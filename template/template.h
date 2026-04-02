/*
 * template.h
 * Description: [DESCRIBE PURPOSE HERE]
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H

#ifdef __cplusplus // if file is being compiled as C++
extern "C" { // enable C-style linkage
#endif // prevents name mangling when included in C code

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */


/* -- Enums / Constants ----------------------------------------------------- */


/* -- Type definitions (structs, typedefs) ---------------------------------- */


/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration (C++ only) ------------------------------------------ */

#ifdef __cplusplus // if compiling as C++, include class definitions
class Template { // c compiler preprocessor will ignore this entire block
public:
    /* -- Public Constructors / Destructors --------------------------------- */


    /* -- Public initialization methods ------------------------------------- */


    /* -- Public control/action methods ------------------------------------- */


    /* -- Public getters ---------------------------------------------------- */


    /* -- Public setters ---------------------------------------------------- */


private:
    /* -- Private member variables ------------------------------------------ */


    /* -- Private helper methods -------------------------------------------- */

};
#endif  /* __cplusplus */

/* -- C-compatible functions (extern "C" if needed) ------------------------- */


#ifdef __cplusplus
}
#endif

#endif  // TEMPLATE_H
