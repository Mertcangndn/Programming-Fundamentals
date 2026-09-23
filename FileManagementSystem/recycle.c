#include "header.h"

int countChildren(File* file) {
    if (file == NULL) return 0;
    
    int count = 0;
    File* child = file->child;
    
    while (child != NULL) {
        count++;
        if (child->isFolder) {
            count += countChildren(child);
        }
        child = child->sibling;
    }
    
    return count;
}

RecycleBin* initRecycleBin(int timeoutSeconds) {
    RecycleBin* bin = malloc(sizeof(RecycleBin));
    
    bin->root = NULL;
    bin->tail = NULL;
    bin->itemCount = 0;
    bin->timeoutSeconds = timeoutSeconds;
    
    return bin;
}

void buildPath(File* file, char* buffer) {
    if (file == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    if (file->parent != NULL) {
        buildPath(file->parent, buffer);
        strcat(buffer, "/");
    }
    strcat(buffer, file->name);
}

File* findFileParent(File* current, char* fileName) {
    if (current == NULL) return NULL;
    
    File* child = current->child;
    while (child != NULL) {
        if (strcmp(child->name, fileName) == 0) {
            return current;
        }
        child = child->sibling;
    }
    
    child = current->child;
    while (child != NULL) {
        if (child->isFolder) {
            File* found = findFileParent(child, fileName);
            if (found != NULL) return found;
        }
        child = child->sibling;
    }
    
    return NULL;
}

int deleteFile(File* root, char* fileName, RecycleBin* bin) {
    if (root == NULL || bin == NULL) {
        return 0;
    }
    
    File* parent = findFileParent(root, fileName);
    
    if (parent == NULL) {
        printf("[HATA] Dosya bulunamadi: %s\n", fileName);
        return 0;
    }
    
    File* current = parent->child;
    File* previous = NULL;
    
    while (current != NULL && strcmp(current->name, fileName) != 0) {
        previous = current;
        current = current->sibling;
    }
    
    if (previous == NULL) {
        parent->child = current->sibling;
    } else {
        previous->sibling = current->sibling;
    }
    
    current->sibling = NULL;
    current->parent = NULL;
    
    current->deletedTime = time(NULL);
    
    buildPath(parent, current->originalPath);
    
    current->sibling = NULL;
    
    if (bin->root == NULL) {
        bin->root = current;
        bin->tail = current;
    } else {
        bin->tail->sibling = current;
        bin->tail = current;
    }
    bin->itemCount++;
    
    printf("[SILINDI] '%s' geri donusum kutusuna tasindi (kuyruga eklendi).\n", fileName);
    return 1;
}

void clearPath(File* file) {
    if (file == NULL) {
        return;
    }
    
    if (file->child != NULL) {
        clearPath(file->child);
        file->child = NULL;
    }
    
    if (file->sibling != NULL) {
        clearPath(file->sibling);
        file->sibling = NULL;
    }
    
    file->originalPath[0] = '\0';
    file->deletedTime = 0;
}

File* findFileByName(File* current, char* name) {
    if (current == NULL) return NULL;
    
    if (strcmp(current->name, name) == 0) {
        return current;
    }
    
    File* child = current->child;
    while (child != NULL) {
        File* found = findFileByName(child, name);
        if (found != NULL) return found;
        child = child->sibling;
    }
    
    return NULL;
}

int restoreFile(RecycleBin* bin, char* fileName, File* root) {
    if (bin == NULL || root == NULL) {
        printf("[HATA] Geri donusum kutusu baslatilamadi!\n");
        return 0;
    }
    
    if (bin->root == NULL) {
        printf("[HATA] Geri donusum kutusu bos! Geri yuklenecek dosya yok.\n");
        return 0;
    }
    
    File* current = bin->root;
    File* previous = NULL;
    
    while (current != NULL && strcmp(current->name, fileName) != 0) {
        previous = current;
        current = current->sibling;
    }
    
    if (current == NULL) {
        printf("[HATA] Dosya geri donusum kutusunda bulunamadi: %s\n", fileName);
        return 0;
    }
    
    char originalPath[MAX_PATH_LENGTH];
    strcpy(originalPath, current->originalPath);
    File* targetParent = root;
    
    if (strlen(originalPath) > 0) {
        char* lastSlash = strrchr(originalPath, '/');
        if (lastSlash != NULL) {
            char parentName[MAX_FILENAME];
            strcpy(parentName, lastSlash + 1);
            
            if (strlen(parentName) > 0) {
                File* foundParent = findFileByName(root, parentName);
                if (foundParent != NULL && foundParent->isFolder) {
                    targetParent = foundParent;
                }
            }
        } else {
            if (strcmp(originalPath, root->name) != 0) {
                File* foundParent = findFileByName(root, originalPath);
                if (foundParent != NULL && foundParent->isFolder) {
                    targetParent = foundParent;
                }
            }
        }
    }
    
    if (previous == NULL) {
        bin->root = current->sibling;
    } else {
        previous->sibling = current->sibling;
    }
    
    if (current == bin->tail) {
        bin->tail = previous;
    }
    
    if (bin->root == NULL) {
        bin->tail = NULL;
    }
    
    bin->itemCount--;
    
    current->sibling = targetParent->child;
    targetParent->child = current;
    current->parent = targetParent;
    
    current->deletedTime = 0;
    current->originalPath[0] = '\0';
    
    printf("[GERI YUKLENDI] '%s' -> '%s' altina geri yuklendi.\n", fileName, targetParent->name);
    return 1;
}

void autoCleanRecycleBin(RecycleBin* bin) {
    if (bin == NULL || bin->root == NULL) {
        return;
    }
    
    time_t currentTime = time(NULL);
    File* current = bin->root;
    File* previous = NULL;
    
    while (current != NULL) {
        double elapsedSeconds = difftime(currentTime, current->deletedTime);
        
        if (elapsedSeconds >= bin->timeoutSeconds) {
            printf("\n[OTOMATIK SILINDI] '%s' suresi doldu ve kalici olarak silindi.\n", 
                   current->name);
            
            File* toDelete = current;
            
            if (previous == NULL) {
                bin->root = current->sibling;
                current = bin->root;
            } else {
                previous->sibling = current->sibling;
                current = previous->sibling;
            }
            
            if (toDelete == bin->tail) {
                bin->tail = previous;
            }
            
            if (bin->root == NULL) {
                bin->tail = NULL;
            }
            
            bin->itemCount--;
            
            clearPath(toDelete);
            freeFile(toDelete);
        } else {
            previous = current;
            current = current->sibling;
        }
    }
}

void freeFile(File* file) {
    if (file == NULL) {
        return;
    }
    
    if (file->child != NULL) {
        freeFile(file->child);
    }
    
    if (file->sibling != NULL) {
        freeFile(file->sibling);
    }
    
    free(file);
}

void listRecycleBin(RecycleBin* bin) {
    if (bin == NULL) {
        printf("[HATA] Geri donusum kutusu baslatilamadi!\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("       GERI DONUSUM KUTUSU\n");
    printf("========================================\n");
    printf("Dosya Sayisi: %d\n", bin->itemCount);
    printf("Zaman Asimi: %d saniye\n", bin->timeoutSeconds);
    printf("----------------------------------------\n");
    
    if (bin->root == NULL) {
        printf("(Geri donusum kutusu bos)\n");
    } else {
        File* current = bin->root;
        time_t currentTime = time(NULL);
        int index = 1;
        
        while (current != NULL) {
            double elapsedSeconds = difftime(currentTime, current->deletedTime);
            double remainingSeconds = bin->timeoutSeconds - elapsedSeconds;
            
            printf("\n%d. ", index++);
            if (current->isFolder) {
                int childCount = countChildren(current);
                printf("[Klasor] %s", current->name);
                if (childCount > 0) {
                    printf(" (%d alt oge ile birlikte)", childCount);
                }
                printf("\n");
            } else {
                printf("[Dosya]  %s\n", current->name);
            }
            printf("   Orijinal Konum: %s\n", current->originalPath);
            printf("   Kalan Sure: %.0f saniye\n", remainingSeconds > 0 ? remainingSeconds : 0);
            
            current = current->sibling;
        }
    }
    
    printf("\n========================================\n");
}