#include "../0x_includes/ext.h"

void file_callback(const char *path) {
    printf("[+] Uploading: %s\n", path);
    if (upload_file(path) == 0)
        printf("[+] Uploaded successfully!\n");
    else
        printf("[-] Upload failed\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <folder_path>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        fprintf(stderr, "Error: Cannot access path '%s'\n", argv[1]);
        return 1;
    }
    
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: '%s' is not a directory\n", argv[1]);
        return 1;
    }
    
    traverse_folder(argv[1], file_callback);
    return 0;
}

