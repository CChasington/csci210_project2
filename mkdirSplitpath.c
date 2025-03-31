#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
    
    printf("TO BE IMPLEMENTED\n");

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

    char* last_slash = strrchr(pathName, '/');
	
    *last_slash = '\0'; // split that string into two

    strcpy(dirName, pathName);
    strcpy(baseName, last_slash + 1);

    struct NODE* currentNode; // node that will go down the tree
    
    if (pathName[0] == '/') {
        currentNode = root;
        pathName = pathName + 1; // advance pathname forward so the root indicator doesnt screw with delimiter
    } else currentNode = cwd; // set it to either absolute or relative

    char *token = strtok(pathName, "/");

    while (token != NULL) { // loop over every delimited directory name
	if (currentNode->childPtr == NULL) {
	    printf("ERROR: directory %s does not exist\n", token);
	    return NULL; // quit if there is more to search for but dir is empty
	}
        
	currentNode = currentNode->childPtr;
        while (strcmp(currentNode->name,"") != 0) { // if the name of the current node doesn't match
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
