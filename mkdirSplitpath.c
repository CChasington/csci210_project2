#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
    
    if (strcmp(pathName, "/") == 0) { // path is root alone, none specificed
        printf("MKDIR ERROR: no path provided\n");
	return;
    }
    char* baseName = malloc(strlen(pathName) + 1);
    char* dirName = malloc(strlen(pathName) + 1);

    struct NODE* parentNode = splitPath(pathName, baseName, dirName);

    free(dirName); // dont need it
    if (parentNode == NULL) return;

    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    strcpy(newNode->name,baseName);
    newNode->fileType = 'D';
    newNode->parentPtr = parentNode;
    newNode->childPtr = NULL;
    newNode->siblingPtr = NULL;
   
    if (parentNode->childPtr != NULL) { // check if it has children to ensure none of them are the dir we are making
        struct NODE* siblingNode = parentNode;
        struct NODE* currentNode = parentNode->childPtr;

        while (currentNode != NULL) { // go through each sibling
	    if (strcmp(currentNode->name,baseName) == 0) { // if it has the same name, quit
	        printf("MKDIR ERROR: directory %s already exists\n", pathName);
	    	return;
	    }
	    siblingNode = currentNode;
	    currentNode = currentNode->siblingPtr;
	}

	siblingNode->siblingPtr = newNode;
    } else {
    	parentNode->childPtr = newNode;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    if (strcmp(pathName, "/") == 0) { // if path is root alone
	strcpy(dirName, "/");
	strcpy(baseName, "");
	return root;
    }

    if (strchr(pathName, '/') == NULL) { // if path is relative file name alone
        strcpy(dirName, "");
	strcpy(baseName, pathName);
	return cwd;
    }

    char *tempPathName = malloc(strlen(pathName) + 1);
    strcpy(tempPathName, pathName);

    char* last_slash = strrchr(tempPathName, '/');
	
    *last_slash = '\0'; // split that string into two

    strcpy(dirName, tempPathName);
    strcpy(baseName, last_slash + 1);

    struct NODE* currentNode; // node that will go down the tree
    
    if (tempPathName[0] == '/') {
        currentNode = root;
        tempPathName = tempPathName + 1; // advance pathname forward so the root indicator doesnt screw with delimiter
    } else currentNode = cwd; // set it to either absolute or relative

    char *token = strtok(tempPathName, "/");

    while (token != NULL) { // loop over every delimited directory name
	if (currentNode->childPtr == NULL) {
	    printf("ERROR: directory %s does not exist\n", token);
	    return NULL; // quit if there is more to search for but dir is empty
	}
      	
	currentNode = currentNode->childPtr;
        while (strcmp(currentNode->name,token) != 0) { // if the name of the current node doesn't match
	    if (currentNode->siblingPtr == NULL) {
	        printf("ERROR: directory %s does not exist\n", token);
	        return NULL; // quit if there is no directories left to search
	    }

	    currentNode = currentNode->siblingPtr; // check the next sibling
	}

	// reaching this point means a child directory with the name was located. currentNode cannot be null

        token = strtok(NULL, "/");
    } 

    return currentNode;
}
