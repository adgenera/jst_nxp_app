#ifndef COMPILER_H
#define COMPILER_H

/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */
#include <Compiler_Cfg.h>

/****************************** typedefs     ******************************** */

/****************************** #defines     ******************************** */
#define COMPILER_VENDOR_ID             99 /**<\brief CoSyst VendorID */
#define COMPILER_AR_MAJOR_VERSION      3  /**<\brief AUTOSAR major version */
#define COMPILER_AR_MINOR_VERSION      1  /**<\brief AUTOSAR minor version */
#define COMPILER_AR_PATCH_VERSION      0  /**<\brief AUTOSAR patch version */
#define COMPILER_SW_MAJOR_VERSION      1  /**<\brief Software major version */
#define COMPILER_SW_MINOR_VERSION      0  /**<\brief Software minor version */
#define COMPILER_SW_PATCH_VERSION      0  /**<\brief Software patch version \n */



/**
* \brief Defines used compiler and platform
*
* Defines used compiler and platform. Example: \<COMPILERNAME\>_C_\<
* PLATFORMNAME\>_
* \note
* Only one define shall be active. The other should be comment out
*/
#define CODEWARRIOR_C_S12Z_
/* #define CODEWARRIOR_C_MPC565_ */
/* #define CODEWARRIOR_C_S08_ */
/* #define GREENHILLS_C_NPCV850_ */
/* #define ICC_C_S12X_ */
/* #define ICC_C_S08_ */
/* #define TASKING_C_TC1796_ */
/* #define TASKING_C_TC1766_ */


/** \cond */
#ifndef CODEWARRIOR_C_S12Z_
/** \endcond */
   /**
   * \brief Definition of keyword AUTOMATIC
   *
   * Shall used for the declaration of local pointers
   */
   #define  AUTOMATIC
   /**
   * \brief Definition of keyword TYPEDEF
   *
   * This memory class shall be used within type definitions, where no
   * memory qualifier can be specified
   */
   #define  TYPEDEF
   /**
   * \brief Definition of keyword STATIC
   *
   * The compiler abstraction shall provide the STATIC define for
   * abstraction of compiler keyword static
   */
   #define  STATIC static
   /**
   * \brief Definition of keyword NULL_PTR
   *
   * The compiler abstraction shall provide the NULL_PTR define with a
   * void pointer to zero definition
   */
   #define  NULL_PTR  ((void *) 0)
   /**
   * \brief Definition of keyword INLINE
   *
   * The compiler abstraction shall provide the INLINE define for
   * abstraction of keyword inline
   */
   #define  INLINE inline
   /**
   * \brief Definition of keyword FUNC
   *
   * The compiler abstraction shall define the FUNC macro for the
   * declaration and definition of functions, that ensures correct syntax of
   * function declarations as required be a specific compiler
   */
   #define  FUNC(rettype, memclass) rettype memclass
   /**
   * \brief Definition of keyword P2VAR
   *
   * The compiler abstraction shall define the P2VAR macro for the declaration
   * and definition of pointers in RAM, pointing to variables
   */
   #define  P2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * memclass
   /**
   * \brief Definition of keyword P2CONST
   *
   * The compiler abstraction shall define the P2CONST macro for the declaration
   * and definition of pointers in RAM, pointing to constants
   */
   #define  P2CONST(ptrtype, memclass, ptrclass) \
                    const ptrtype memclass * ptrclass
   /**
   * \brief Definition of keyword CONSTP2VAR
   *
   * The compiler abstraction shall define the CONSTP2VAR macro for the
   * declaration and definition of constant pointers accessing variables
   */
   #define  CONSTP2VAR(ptrtype, memclass, ptrclass) \
                       ptrclass ptrtype* const memclass
   /**
   * \brief Definition of keyword CONSTP2CONST
   *
   * The compiler abstraction shall define the CONSTP2CONST macro for the
   * declaration and definition of constant pointers accessing constants
   */
   #define  CONSTP2CONST(ptrtype, memclass, ptrclass) \
                         const memclass ptrtype * const ptrclass
   /**
   * \brief Definition of keyword P2FUNC
   *
   * The compiler abstraction shall define the P2FUNC macro for the
   * definition of pointers to functions
   */
   #define  P2FUNC(rettype, ptrclass, fctname) rettype (*ptrclass fctname)
   /**
   * \brief Definition of keyword CONST
   *
   * The compiler abstraction shall define the CONST macro for the
   * declaration and definition of constants
   */
   #define  CONST(consttype, memclass) memclass const type
   /**
   * \brief Definition of keyword VAR
   *
   * The compiler abstraction shall define the VAR macro for the
   * declaration and definition of variables
   */
   #define  VAR(vartype, memclass) memclass type

#endif /* CODEWARRIOR_C_S12Z_ */



/** \cond */
#ifndef ICC_C_S12Z_
   /**
   * \brief Definition of keyword AUTOMATIC
   *
   * Shall used for the declaration of local pointers
   */
   #define  AUTOMATIC
   /**
   * \brief Definition of keyword TYPEDEF
   *
   * This memory class shall be used within type definitions, where no
   * memory qualifier can be specified
   */
   #define  TYPEDEF
   /**
   * \brief Definition of keyword STATIC
   *
   * The compiler abstraction shall provide the STATIC define for
   * abstraction of compiler keyword static
   */
   #define  STATIC static
   /**
   * \brief Definition of keyword NULL_PTR
   *
   * The compiler abstraction shall provide the NULL_PTR define with a
   * void pointer to zero definition
   */
   #define  NULL_PTR  ((void *) 0)
   /**
   * \brief Definition of keyword INLINE
   *
   * The compiler abstraction shall provide the INLINE define for
   * abstraction of keyword inline
   */
   #define  INLINE inline
   /**
   * \brief Definition of keyword FUNC
   *
   * The compiler abstraction shall define the FUNC macro for the
   * declaration and definition of functions, that ensures correct syntax of
   * function declarations as required be a specific compiler
   */
   #define  FUNC(rettype, memclass)
   /**
   * \brief Definition of keyword P2VAR
   *
   * The compiler abstraction shall define the P2VAR macro for the declaration
   * and definition of pointers in RAM, pointing to variables
   */
   #define  P2VAR(ptrtype, memclass, ptrclass)
   /**
   * \brief Definition of keyword P2CONST
   *
   * The compiler abstraction shall define the P2CONST macro for the declaration
   * and definition of pointers in RAM, pointing to constants
   */
   #define  P2CONST(ptrtype, memclass, ptrclass)
   /**
   * \brief Definition of keyword CONSTP2VAR
   *
   * The compiler abstraction shall define the CONSTP2VAR macro for the
   * declaration and definition of constant pointers accessing variables
   */
   #define  CONSTP2VAR(ptrtype, memclass, ptrclass)
   /**
   * \brief Definition of keyword CONSTP2CONST
   *
   * The compiler abstraction shall define the CONSTP2CONST macro for the
   * declaration and definition of constant pointers accessing constants
   */
   #define  CONSTP2CONST(ptrtype, memclass, ptrclass)
   /**
   * \brief Definition of keyword P2FUNC
   *
   * The compiler abstraction shall define the P2FUNC macro for the
   * definition of pointers to functions
   */
   #define  P2FUNC(rettype, ptrclass, fctname)
   /**
   * \brief Definition of keyword CONST
   *
   * The compiler abstraction shall define the CONST macro for the
   * declaration and definition of constants
   */
   #define  CONST(consttype, memclass)
   /**
   * \brief Definition of keyword VAR
   *
   * The compiler abstraction shall define the VAR macro for the
   * declaration and definition of variables
   */
   #define  VAR(vartype, memclass)

#endif /* ICC_C_S12Z_ */
/** \endcond */

/****************************** enums        ******************************** */

/****************************** structs      ******************************** */

/****************************** modul global data  ************************** */

/****************************** global data  ******************************** */

/****************************** prototypes   ******************************** */

#endif /* COMPILER_H */
