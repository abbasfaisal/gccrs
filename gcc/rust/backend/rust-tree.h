// Copyright (C) 2020-2022 Free Software Foundation, Inc.

// This file is part of GCC.

// GCC is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3, or (at your option) any later
// version.

// GCC is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#ifndef RUST_TREE
#define RUST_TREE

#include "rust-system.h"
#include "coretypes.h"
#include "tree.h"

/* Returns true if NODE is a pointer.  */
#define TYPE_PTR_P(NODE) (TREE_CODE (NODE) == POINTER_TYPE)

/* Returns true if NODE is a reference.  */
#define TYPE_REF_P(NODE) (TREE_CODE (NODE) == REFERENCE_TYPE)

/* Returns true if NODE is a pointer or a reference.  */
#define INDIRECT_TYPE_P(NODE) (TYPE_PTR_P (NODE) || TYPE_REF_P (NODE))

/* [basic.fundamental]

   Types  bool, char, wchar_t, and the signed and unsigned integer types
   are collectively called integral types.

   Note that INTEGRAL_TYPE_P, as defined in tree.h, allows enumeration
   types as well, which is incorrect in C++.  Keep these checks in
   ascending code order.  */
#define RS_INTEGRAL_TYPE_P(TYPE)                                               \
  (TREE_CODE (TYPE) == BOOLEAN_TYPE || TREE_CODE (TYPE) == INTEGER_TYPE)

/* True iff TYPE is cv decltype(nullptr).  */
#define NULLPTR_TYPE_P(TYPE) (TREE_CODE (TYPE) == NULLPTR_TYPE)

/* True if NODE is an implicit INDIRECT_REF from convert_from_reference.  */
#define REFERENCE_REF_P(NODE)                                                  \
  (INDIRECT_REF_P (NODE) && TREE_TYPE (TREE_OPERAND (NODE, 0))                 \
   && TYPE_REF_P (TREE_TYPE (TREE_OPERAND ((NODE), 0))))

// this is a helper to differentiate RECORD types between actual records and
// slices
#define SLICE_FLAG TREE_LANG_FLAG_0
#define SLICE_TYPE_P(TYPE)                                                     \
  (TREE_CODE (TYPE) == RECORD_TYPE && TREE_LANG_FLAG_0 (TYPE))

/* Usage of TREE_LANG_FLAG_?:
   0: IDENTIFIER_KIND_BIT_0 (in IDENTIFIER_NODE)
      NEW_EXPR_USE_GLOBAL (in NEW_EXPR).
      COND_EXPR_IS_VEC_DELETE (in COND_EXPR).
      DELETE_EXPR_USE_GLOBAL (in DELETE_EXPR).
      CLEANUP_P (in TRY_BLOCK)
      AGGR_INIT_VIA_CTOR_P (in AGGR_INIT_EXPR)
      PTRMEM_OK_P (in ADDR_EXPR, OFFSET_REF, SCOPE_REF)
      PAREN_STRING_LITERAL_P (in STRING_CST)
      CP_DECL_THREAD_LOCAL_P (in VAR_DECL)
      KOENIG_LOOKUP_P (in CALL_EXPR)
      STATEMENT_LIST_NO_SCOPE (in STATEMENT_LIST).
      EXPR_STMT_STMT_EXPR_RESULT (in EXPR_STMT)
      STMT_EXPR_NO_SCOPE (in STMT_EXPR)
      BIND_EXPR_TRY_BLOCK (in BIND_EXPR)
      TYPENAME_IS_ENUM_P (in TYPENAME_TYPE)
      OMP_FOR_GIMPLIFYING_P (in OMP_FOR, OMP_SIMD, OMP_DISTRIBUTE,
			     and OMP_TASKLOOP)
      BASELINK_QUALIFIED_P (in BASELINK)
      TARGET_EXPR_IMPLICIT_P (in TARGET_EXPR)
      TEMPLATE_PARM_PARAMETER_PACK (in TEMPLATE_PARM_INDEX)
      ATTR_IS_DEPENDENT (in the TREE_LIST for an attribute)
      ABI_TAG_IMPLICIT (in the TREE_LIST for the argument of abi_tag)
      LAMBDA_CAPTURE_EXPLICIT_P (in a TREE_LIST in LAMBDA_EXPR_CAPTURE_LIST)
      PARENTHESIZED_LIST_P (in the TREE_LIST for a parameter-declaration-list)
      CONSTRUCTOR_IS_DIRECT_INIT (in CONSTRUCTOR)
      LAMBDA_EXPR_CAPTURES_THIS_P (in LAMBDA_EXPR)
      DECLTYPE_FOR_LAMBDA_CAPTURE (in DECLTYPE_TYPE)
      VEC_INIT_EXPR_IS_CONSTEXPR (in VEC_INIT_EXPR)
      DECL_OVERRIDE_P (in FUNCTION_DECL)
      IMPLICIT_CONV_EXPR_DIRECT_INIT (in IMPLICIT_CONV_EXPR)
      TRANSACTION_EXPR_IS_STMT (in TRANSACTION_EXPR)
      CONVERT_EXPR_VBASE_PATH (in CONVERT_EXPR)
      PACK_EXPANSION_LOCAL_P (in *_PACK_EXPANSION)
      TINFO_HAS_ACCESS_ERRORS (in TEMPLATE_INFO)
      SIZEOF_EXPR_TYPE_P (in SIZEOF_EXPR)
      COMPOUND_REQ_NOEXCEPT_P (in COMPOUND_REQ)
      WILDCARD_PACK_P (in WILDCARD_DECL)
      BLOCK_OUTER_CURLY_BRACE_P (in BLOCK)
      FOLD_EXPR_MODOP_P (*_FOLD_EXPR)
      IF_STMT_CONSTEXPR_P (IF_STMT)
      DECL_NAMESPACE_INLINE_P (in NAMESPACE_DECL)
      SWITCH_STMT_ALL_CASES_P (in SWITCH_STMT)
      REINTERPRET_CAST_P (in NOP_EXPR)
      ALIGNOF_EXPR_STD_P (in ALIGNOF_EXPR)
      OVL_DEDUP_P (in OVERLOAD)
      ATOMIC_CONSTR_MAP_INSTANTIATED_P (in ATOMIC_CONSTR)
   1: IDENTIFIER_KIND_BIT_1 (in IDENTIFIER_NODE)
      TI_PENDING_TEMPLATE_FLAG.
      TEMPLATE_PARMS_FOR_INLINE.
      DELETE_EXPR_USE_VEC (in DELETE_EXPR).
      (TREE_CALLS_NEW) (in _EXPR or _REF) (commented-out).
      ICS_ELLIPSIS_FLAG (in _CONV)
      DECL_INITIALIZED_P (in VAR_DECL)
      TYPENAME_IS_CLASS_P (in TYPENAME_TYPE)
      STMT_IS_FULL_EXPR_P (in _STMT)
      TARGET_EXPR_LIST_INIT_P (in TARGET_EXPR)
      LAMBDA_EXPR_MUTABLE_P (in LAMBDA_EXPR)
      DECL_FINAL_P (in FUNCTION_DECL)
      QUALIFIED_NAME_IS_TEMPLATE (in SCOPE_REF)
      CONSTRUCTOR_IS_DEPENDENT (in CONSTRUCTOR)
      TINFO_USED_TEMPLATE_ID (in TEMPLATE_INFO)
      PACK_EXPANSION_SIZEOF_P (in *_PACK_EXPANSION)
      OVL_USING_P (in OVERLOAD)
      IMPLICIT_CONV_EXPR_NONTYPE_ARG (in IMPLICIT_CONV_EXPR)
      BASELINK_FUNCTIONS_MAYBE_INCOMPLETE_P (in BASELINK)
      BIND_EXPR_VEC_DTOR (in BIND_EXPR)
   2: IDENTIFIER_KIND_BIT_2 (in IDENTIFIER_NODE)
      ICS_THIS_FLAG (in _CONV)
      DECL_INITIALIZED_BY_CONSTANT_EXPRESSION_P (in VAR_DECL)
      STATEMENT_LIST_TRY_BLOCK (in STATEMENT_LIST)
      TYPENAME_IS_RESOLVING_P (in TYPENAME_TYPE)
      TARGET_EXPR_DIRECT_INIT_P (in TARGET_EXPR)
      FNDECL_USED_AUTO (in FUNCTION_DECL)
      DECLTYPE_FOR_LAMBDA_PROXY (in DECLTYPE_TYPE)
      REF_PARENTHESIZED_P (in COMPONENT_REF, INDIRECT_REF, SCOPE_REF,
			   VIEW_CONVERT_EXPR, PAREN_EXPR)
      AGGR_INIT_ZERO_FIRST (in AGGR_INIT_EXPR)
      CONSTRUCTOR_MUTABLE_POISON (in CONSTRUCTOR)
      OVL_HIDDEN_P (in OVERLOAD)
      IF_STMT_CONSTEVAL_P (in IF_STMT)
      SWITCH_STMT_NO_BREAK_P (in SWITCH_STMT)
      LAMBDA_EXPR_CAPTURE_OPTIMIZED (in LAMBDA_EXPR)
      IMPLICIT_CONV_EXPR_BRACED_INIT (in IMPLICIT_CONV_EXPR)
      PACK_EXPANSION_AUTO_P (in *_PACK_EXPANSION)
   3: IMPLICIT_RVALUE_P (in NON_LVALUE_EXPR or STATIC_CAST_EXPR)
      ICS_BAD_FLAG (in _CONV)
      FN_TRY_BLOCK_P (in TRY_BLOCK)
      BIND_EXPR_BODY_BLOCK (in BIND_EXPR)
      CALL_EXPR_ORDERED_ARGS (in CALL_EXPR, AGGR_INIT_EXPR)
      DECLTYPE_FOR_REF_CAPTURE (in DECLTYPE_TYPE)
      CONSTRUCTOR_C99_COMPOUND_LITERAL (in CONSTRUCTOR)
      OVL_NESTED_P (in OVERLOAD)
      DECL_MODULE_EXPORT_P (in _DECL)
      PACK_EXPANSION_FORCE_EXTRA_ARGS_P (in *_PACK_EXPANSION)
   4: IDENTIFIER_MARKED (IDENTIFIER_NODEs)
      TREE_HAS_CONSTRUCTOR (in INDIRECT_REF, SAVE_EXPR, CONSTRUCTOR,
	  CALL_EXPR, or FIELD_DECL).
      DECL_TINFO_P (in VAR_DECL, TYPE_DECL)
      FUNCTION_REF_QUALIFIED (in FUNCTION_TYPE, METHOD_TYPE)
      OVL_LOOKUP_P (in OVERLOAD)
      LOOKUP_FOUND_P (in RECORD_TYPE, UNION_TYPE, ENUMERAL_TYPE, NAMESPACE_DECL)
      FNDECL_MANIFESTLY_CONST_EVALUATED (in FUNCTION_DECL)
   5: IDENTIFIER_VIRTUAL_P (in IDENTIFIER_NODE)
      FUNCTION_RVALUE_QUALIFIED (in FUNCTION_TYPE, METHOD_TYPE)
      CALL_EXPR_REVERSE_ARGS (in CALL_EXPR, AGGR_INIT_EXPR)
      CONSTRUCTOR_PLACEHOLDER_BOUNDARY (in CONSTRUCTOR)
      OVL_EXPORT_P (in OVERLOAD)
   6: TYPE_MARKED_P (in _TYPE)
      DECL_NONTRIVIALLY_INITIALIZED_P (in VAR_DECL)
      RANGE_FOR_IVDEP (in RANGE_FOR_STMT)
      CALL_EXPR_OPERATOR_SYNTAX (in CALL_EXPR, AGGR_INIT_EXPR)
      CONSTRUCTOR_IS_DESIGNATED_INIT (in CONSTRUCTOR)

   Usage of TYPE_LANG_FLAG_?:
   0: TYPE_DEPENDENT_P
   1: TYPE_HAS_USER_CONSTRUCTOR.
   2: TYPE_HAS_LATE_RETURN_TYPE (in FUNCTION_TYPE, METHOD_TYPE)
      TYPE_PTRMEMFUNC_FLAG (in RECORD_TYPE)
   4: TYPE_HAS_NONTRIVIAL_DESTRUCTOR
   5: CLASS_TYPE_P (in RECORD_TYPE and UNION_TYPE)
      ENUM_FIXED_UNDERLYING_TYPE_P (in ENUMERAL_TYPE)
      AUTO_IS_DECLTYPE (in TEMPLATE_TYPE_PARM)
   6: TYPE_DEPENDENT_P_VALID

   Usage of DECL_LANG_FLAG_?:
   0: DECL_TEMPLATE_PARM_P (in PARM_DECL, CONST_DECL, TYPE_DECL, or
  TEMPLATE_DECL) DECL_LOCAL_DECL_P (in FUNCTION_DECL, VAR_DECL) DECL_MUTABLE_P
  (in FIELD_DECL) DECL_DEPENDENT_P (in USING_DECL) LABEL_DECL_BREAK (in
  LABEL_DECL) 1: C_TYPEDEF_EXPLICITLY_SIGNED (in TYPE_DECL).
      DECL_TEMPLATE_INSTANTIATED (in a VAR_DECL or a FUNCTION_DECL)
      DECL_MEMBER_TEMPLATE_P (in TEMPLATE_DECL)
      USING_DECL_TYPENAME_P (in USING_DECL)
      DECL_VLA_CAPTURE_P (in FIELD_DECL)
      DECL_ARRAY_PARAMETER_P (in PARM_DECL)
      LABEL_DECL_CONTINUE (in LABEL_DECL)
   2: DECL_THIS_EXTERN (in VAR_DECL, FUNCTION_DECL or PARM_DECL)
      DECL_IMPLICIT_TYPEDEF_P (in a TYPE_DECL)
      DECL_CONSTRAINT_VAR_P (in a PARM_DECL)
      TEMPLATE_DECL_COMPLEX_ALIAS_P (in TEMPLATE_DECL)
      DECL_INSTANTIATING_NSDMI_P (in a FIELD_DECL)
      LABEL_DECL_CDTOR (in LABEL_DECL)
      USING_DECL_UNRELATED_P (in USING_DECL)
   3: DECL_IN_AGGR_P.
   4: DECL_C_BIT_FIELD (in a FIELD_DECL)
      DECL_ANON_UNION_VAR_P (in a VAR_DECL)
      DECL_SELF_REFERENCE_P (in a TYPE_DECL)
      DECL_INVALID_OVERRIDER_P (in a FUNCTION_DECL)
      DECL_UNINSTANIATED_TEMPLATE_FRIEND_P (in TEMPLATE_DECL)
   5: DECL_INTERFACE_KNOWN.
   6: DECL_THIS_STATIC (in VAR_DECL, FUNCTION_DECL or PARM_DECL)
      DECL_FIELD_IS_BASE (in FIELD_DECL)
      TYPE_DECL_ALIAS_P (in TYPE_DECL)
   7: DECL_THUNK_P (in a member FUNCTION_DECL)
      DECL_NORMAL_CAPTURE_P (in FIELD_DECL)
      DECL_DECLARED_CONSTINIT_P (in VAR_DECL)
   8: DECL_DECLARED_CONSTEXPR_P (in VAR_DECL, FUNCTION_DECL)

   Usage of language-independent fields in a language-dependent manner:

   TYPE_ALIAS_SET
     This field is used by TYPENAME_TYPEs, TEMPLATE_TYPE_PARMs, and so
     forth as a substitute for the mark bits provided in `lang_type'.
     At present, only the six low-order bits are used.

   TYPE_LANG_SLOT_1
     For a FUNCTION_TYPE or METHOD_TYPE, this is TYPE_RAISES_EXCEPTIONS.
     For a POINTER_TYPE (to a METHOD_TYPE), this is TYPE_PTRMEMFUNC_TYPE.
     For an ENUMERAL_TYPE, BOUND_TEMPLATE_TEMPLATE_PARM_TYPE,
     RECORD_TYPE or UNION_TYPE this is TYPE_TEMPLATE_INFO,

  BINFO_VIRTUALS
     For a binfo, this is a TREE_LIST.  There is an entry for each
     virtual function declared either in BINFO or its direct and
     indirect primary bases.

     The BV_DELTA of each node gives the amount by which to adjust the
     `this' pointer when calling the function.  If the method is an
     overridden version of a base class method, then it is assumed
     that, prior to adjustment, the this pointer points to an object
     of the base class.

     The BV_VCALL_INDEX of each node, if non-NULL, gives the vtable
     index of the vcall offset for this entry.

     The BV_FN is the declaration for the virtual function itself.

     If BV_LOST_PRIMARY is set, it means that this entry is for a lost
     primary virtual base and can be left null in the vtable.

   BINFO_VTABLE
     This is an expression with POINTER_TYPE that gives the value
     to which the vptr should be initialized.  Use get_vtbl_decl_for_binfo
     to extract the VAR_DECL for the complete vtable.

   DECL_VINDEX
     This field is NULL for a non-virtual function.  For a virtual
     function, it is eventually set to an INTEGER_CST indicating the
     index in the vtable at which this function can be found.  When
     a virtual function is declared, but before it is known what
     function is overridden, this field is the error_mark_node.

     Temporarily, it may be set to a TREE_LIST whose TREE_VALUE is
     the virtual function this one overrides, and whose TREE_CHAIN is
     the old DECL_VINDEX.  */

/* Language-specific tree checkers.  */

#define VAR_OR_FUNCTION_DECL_CHECK(NODE)                                       \
  TREE_CHECK2 (NODE, VAR_DECL, FUNCTION_DECL)

#define TYPE_FUNCTION_OR_TEMPLATE_DECL_CHECK(NODE)                             \
  TREE_CHECK3 (NODE, TYPE_DECL, TEMPLATE_DECL, FUNCTION_DECL)

#define TYPE_FUNCTION_OR_TEMPLATE_DECL_P(NODE)                                 \
  (TREE_CODE (NODE) == TYPE_DECL || TREE_CODE (NODE) == TEMPLATE_DECL          \
   || TREE_CODE (NODE) == FUNCTION_DECL)

#define VAR_FUNCTION_OR_PARM_DECL_CHECK(NODE)                                  \
  TREE_CHECK3 (NODE, VAR_DECL, FUNCTION_DECL, PARM_DECL)

#define VAR_TEMPL_TYPE_OR_FUNCTION_DECL_CHECK(NODE)                            \
  TREE_CHECK4 (NODE, VAR_DECL, FUNCTION_DECL, TYPE_DECL, TEMPLATE_DECL)

#define VAR_TEMPL_TYPE_FIELD_OR_FUNCTION_DECL_CHECK(NODE)                      \
  TREE_CHECK5 (NODE, VAR_DECL, FIELD_DECL, FUNCTION_DECL, TYPE_DECL,           \
	       TEMPLATE_DECL)

#define BOUND_TEMPLATE_TEMPLATE_PARM_TYPE_CHECK(NODE)                          \
  TREE_CHECK (NODE, BOUND_TEMPLATE_TEMPLATE_PARM)

#if defined ENABLE_TREE_CHECKING && (GCC_VERSION >= 2007)

#define TEMPLATE_INFO_DECL_CHECK(NODE)                                         \
  template_info_decl_check ((NODE), __FILE__, __LINE__, __FUNCTION__)

#define THUNK_FUNCTION_CHECK(NODE)                                             \
  __extension__({                                                              \
    __typeof (NODE) const __t = (NODE);                                        \
    if (TREE_CODE (__t) != FUNCTION_DECL || !__t->decl_common.lang_specific    \
	|| !__t->decl_common.lang_specific->u.fn.thunk_p)                      \
      tree_check_failed (__t, __FILE__, __LINE__, __FUNCTION__, 0);            \
    __t;                                                                       \
  })

#else /* ENABLE_TREE_CHECKING */

#define TEMPLATE_INFO_DECL_CHECK(NODE) (NODE)
#define THUNK_FUNCTION_CHECK(NODE) (NODE)

#endif /* ENABLE_TREE_CHECKING */

#define CLEANUP_P(NODE) TREE_LANG_FLAG_0 (TRY_BLOCK_CHECK (NODE))

#define BIND_EXPR_TRY_BLOCK(NODE) TREE_LANG_FLAG_0 (BIND_EXPR_CHECK (NODE))

/* This BIND_EXPR is from build_vec_delete_1.  */
#define BIND_EXPR_VEC_DTOR(NODE) TREE_LANG_FLAG_1 (BIND_EXPR_CHECK (NODE))

/* Used to mark the block around the member initializers and cleanups.  */
#define BIND_EXPR_BODY_BLOCK(NODE) TREE_LANG_FLAG_3 (BIND_EXPR_CHECK (NODE))
#define FUNCTION_NEEDS_BODY_BLOCK(NODE)                                        \
  (DECL_CONSTRUCTOR_P (NODE) || DECL_DESTRUCTOR_P (NODE)                       \
   || LAMBDA_FUNCTION_P (NODE))

#define STATEMENT_LIST_NO_SCOPE(NODE)                                          \
  TREE_LANG_FLAG_0 (STATEMENT_LIST_CHECK (NODE))
#define STATEMENT_LIST_TRY_BLOCK(NODE)                                         \
  TREE_LANG_FLAG_2 (STATEMENT_LIST_CHECK (NODE))

/* Mark the outer curly brace BLOCK.  */
#define BLOCK_OUTER_CURLY_BRACE_P(NODE) TREE_LANG_FLAG_0 (BLOCK_CHECK (NODE))

/* Nonzero if this statement should be considered a full-expression,
   i.e., if temporaries created during this statement should have
   their destructors run at the end of this statement.  */
#define STMT_IS_FULL_EXPR_P(NODE) TREE_LANG_FLAG_1 ((NODE))

/* Marks the result of a statement expression.  */
#define EXPR_STMT_STMT_EXPR_RESULT(NODE)                                       \
  TREE_LANG_FLAG_0 (EXPR_STMT_CHECK (NODE))

/* Nonzero if this statement-expression does not have an associated scope.  */
#define STMT_EXPR_NO_SCOPE(NODE) TREE_LANG_FLAG_0 (STMT_EXPR_CHECK (NODE))

#define COND_EXPR_IS_VEC_DELETE(NODE) TREE_LANG_FLAG_0 (COND_EXPR_CHECK (NODE))

/* Nonzero if this NOP_EXPR is a reinterpret_cast.  Such conversions
   are not constexprs.  Other NOP_EXPRs are.  */
#define REINTERPRET_CAST_P(NODE) TREE_LANG_FLAG_0 (NOP_EXPR_CHECK (NODE))

/* Returns nonzero iff TYPE1 and TYPE2 are the same type, in the usual
   sense of `same'.  */
#define same_type_p(TYPE1, TYPE2) comptypes ((TYPE1), (TYPE2), COMPARE_STRICT)

/* Returns nonzero iff NODE is a declaration for the global function
   `main'.  */
#define DECL_MAIN_P(NODE)                                                      \
  (DECL_EXTERN_C_FUNCTION_P (NODE) && DECL_NAME (NODE) != NULL_TREE            \
   && MAIN_NAME_P (DECL_NAME (NODE)) && flag_hosted)

/* Lookup walker marking.  */
#define LOOKUP_SEEN_P(NODE) TREE_VISITED (NODE)
#define LOOKUP_FOUND_P(NODE)                                                   \
  TREE_LANG_FLAG_4 (TREE_CHECK4 (NODE, RECORD_TYPE, UNION_TYPE, ENUMERAL_TYPE, \
				 NAMESPACE_DECL))

/* These two accessors should only be used by OVL manipulators.
   Other users should use iterators and convenience functions.  */
#define OVL_FUNCTION(NODE)                                                     \
  (((struct tree_overload *) OVERLOAD_CHECK (NODE))->function)
#define OVL_CHAIN(NODE)                                                        \
  (((struct tree_overload *) OVERLOAD_CHECK (NODE))->common.chain)

/* If set, this or a subsequent overload contains decls that need deduping.  */
#define OVL_DEDUP_P(NODE) TREE_LANG_FLAG_0 (OVERLOAD_CHECK (NODE))
/* If set, this was imported in a using declaration.   */
#define OVL_USING_P(NODE) TREE_LANG_FLAG_1 (OVERLOAD_CHECK (NODE))
/* If set, this overload is a hidden decl.  */
#define OVL_HIDDEN_P(NODE) TREE_LANG_FLAG_2 (OVERLOAD_CHECK (NODE))
/* If set, this overload contains a nested overload.  */
#define OVL_NESTED_P(NODE) TREE_LANG_FLAG_3 (OVERLOAD_CHECK (NODE))
/* If set, this overload was constructed during lookup.  */
#define OVL_LOOKUP_P(NODE) TREE_LANG_FLAG_4 (OVERLOAD_CHECK (NODE))
/* If set, this OVL_USING_P overload is exported.  */
#define OVL_EXPORT_P(NODE) TREE_LANG_FLAG_5 (OVERLOAD_CHECK (NODE))

/* The first decl of an overload.  */
#define OVL_FIRST(NODE) ovl_first (NODE)
/* The name of the overload set.  */
#define OVL_NAME(NODE) DECL_NAME (OVL_FIRST (NODE))

/* Whether this is a set of overloaded functions.  TEMPLATE_DECLS are
   always wrapped in an OVERLOAD, so we don't need to check them
   here.  */
#define OVL_P(NODE)                                                            \
  (TREE_CODE (NODE) == FUNCTION_DECL || TREE_CODE (NODE) == OVERLOAD)
/* Whether this is a single member overload.  */
#define OVL_SINGLE_P(NODE) (TREE_CODE (NODE) != OVERLOAD || !OVL_CHAIN (NODE))

/* Returns true iff NODE is a BASELINK.  */
#define BASELINK_P(NODE) (TREE_CODE (NODE) == BASELINK)
/* The BINFO indicating the base in which lookup found the
   BASELINK_FUNCTIONS.  */
#define BASELINK_BINFO(NODE)                                                   \
  (((struct tree_baselink *) BASELINK_CHECK (NODE))->binfo)
/* The functions referred to by the BASELINK; either a FUNCTION_DECL,
   a TEMPLATE_DECL, an OVERLOAD, or a TEMPLATE_ID_EXPR.  */
#define BASELINK_FUNCTIONS(NODE)                                               \
  (((struct tree_baselink *) BASELINK_CHECK (NODE))->functions)
/* If T is a BASELINK, grab the functions, otherwise just T, which is
   expected to already be a (list of) functions.  */
#define MAYBE_BASELINK_FUNCTIONS(T)                                            \
  (BASELINK_P (T) ? BASELINK_FUNCTIONS (T) : T)
/* The BINFO in which the search for the functions indicated by this baselink
   began.  This base is used to determine the accessibility of functions
   selected by overload resolution.  */
#define BASELINK_ACCESS_BINFO(NODE)                                            \
  (((struct tree_baselink *) BASELINK_CHECK (NODE))->access_binfo)
/* For a type-conversion operator, the BASELINK_OPTYPE indicates the type
   to which the conversion should occur.  This value is important if
   the BASELINK_FUNCTIONS include a template conversion operator --
   the BASELINK_OPTYPE can be used to determine what type the user
   requested.  */
#define BASELINK_OPTYPE(NODE) (TREE_CHAIN (BASELINK_CHECK (NODE)))
/* Nonzero if this baselink was from a qualified lookup.  */
#define BASELINK_QUALIFIED_P(NODE) TREE_LANG_FLAG_0 (BASELINK_CHECK (NODE))
/* Nonzero if the overload set for this baselink might be incomplete due
   to the lookup being performed from an incomplete-class context.  */
#define BASELINK_FUNCTIONS_MAYBE_INCOMPLETE_P(NODE)                            \
  TREE_LANG_FLAG_1 (BASELINK_CHECK (NODE))

/* Identifiers map directly to block or class-scope bindings.
   Namespace-scope bindings are held in hash tables on the respective
   namespaces.  The identifier bindings are the innermost active
   binding, from whence you can get the decl and/or implicit-typedef
   of an elaborated type.   When not bound to a local entity the
   values are NULL.  */
#define IDENTIFIER_BINDING(NODE) (LANG_IDENTIFIER_CAST (NODE)->bindings)
#define REAL_IDENTIFIER_TYPE_VALUE(NODE) TREE_TYPE (NODE)
#define SET_IDENTIFIER_TYPE_VALUE(NODE, TYPE) (TREE_TYPE (NODE) = (TYPE))

/* Kind bits.  */
#define IDENTIFIER_KIND_BIT_0(NODE)                                            \
  TREE_LANG_FLAG_0 (IDENTIFIER_NODE_CHECK (NODE))
#define IDENTIFIER_KIND_BIT_1(NODE)                                            \
  TREE_LANG_FLAG_1 (IDENTIFIER_NODE_CHECK (NODE))
#define IDENTIFIER_KIND_BIT_2(NODE)                                            \
  TREE_LANG_FLAG_2 (IDENTIFIER_NODE_CHECK (NODE))

/* Used by various search routines.  */
#define IDENTIFIER_MARKED(NODE) TREE_LANG_FLAG_4 (IDENTIFIER_NODE_CHECK (NODE))

/* Nonzero if this identifier is used as a virtual function name somewhere
   (optimizes searches).  */
#define IDENTIFIER_VIRTUAL_P(NODE)                                             \
  TREE_LANG_FLAG_5 (IDENTIFIER_NODE_CHECK (NODE))

/* True if this identifier is a reserved word.  C_RID_CODE (node) is
   then the RID_* value of the keyword.  Value 1.  */
#define IDENTIFIER_KEYWORD_P(NODE)                                             \
  ((!IDENTIFIER_KIND_BIT_2 (NODE)) & (!IDENTIFIER_KIND_BIT_1 (NODE))           \
   & IDENTIFIER_KIND_BIT_0 (NODE))

/* True if this identifier is the name of a constructor or
   destructor.  Value 2 or 3.  */
#define IDENTIFIER_CDTOR_P(NODE)                                               \
  ((!IDENTIFIER_KIND_BIT_2 (NODE)) & IDENTIFIER_KIND_BIT_1 (NODE))

/* True if this identifier is the name of a constructor.  Value 2.  */
#define IDENTIFIER_CTOR_P(NODE)                                                \
  (IDENTIFIER_CDTOR_P (NODE) & (!IDENTIFIER_KIND_BIT_0 (NODE)))

/* True if this identifier is the name of a destructor.  Value 3.  */
#define IDENTIFIER_DTOR_P(NODE)                                                \
  (IDENTIFIER_CDTOR_P (NODE) & IDENTIFIER_KIND_BIT_0 (NODE))

/* True if this identifier is for any operator name (including
   conversions).  Value 4, 5, 6 or 7.  */
#define IDENTIFIER_ANY_OP_P(NODE) (IDENTIFIER_KIND_BIT_2 (NODE))

/* True if this identifier is for an overloaded operator. Values 4, 5.  */
#define IDENTIFIER_OVL_OP_P(NODE)                                              \
  (IDENTIFIER_ANY_OP_P (NODE) & (!IDENTIFIER_KIND_BIT_1 (NODE)))

/* True if this identifier is for any assignment. Values 5.  */
#define IDENTIFIER_ASSIGN_OP_P(NODE)                                           \
  (IDENTIFIER_OVL_OP_P (NODE) & IDENTIFIER_KIND_BIT_0 (NODE))

/* True if this identifier is the name of a type-conversion
   operator.  Value 7.  */
#define IDENTIFIER_CONV_OP_P(NODE)                                             \
  (IDENTIFIER_ANY_OP_P (NODE) & IDENTIFIER_KIND_BIT_1 (NODE)                   \
   & (!IDENTIFIER_KIND_BIT_0 (NODE)))

/* True if this identifier is a new or delete operator.  */
#define IDENTIFIER_NEWDEL_OP_P(NODE)                                           \
  (IDENTIFIER_OVL_OP_P (NODE)                                                  \
   && IDENTIFIER_OVL_OP_FLAGS (NODE) & OVL_OP_FLAG_ALLOC)

/* True if this identifier is a new operator.  */
#define IDENTIFIER_NEW_OP_P(NODE)                                              \
  (IDENTIFIER_OVL_OP_P (NODE)                                                  \
   && (IDENTIFIER_OVL_OP_FLAGS (NODE)                                          \
       & (OVL_OP_FLAG_ALLOC | OVL_OP_FLAG_DELETE))                             \
	== OVL_OP_FLAG_ALLOC)

/* Access a C++-specific index for identifier NODE.
   Used to optimize operator mappings etc.  */
#define IDENTIFIER_CP_INDEX(NODE)                                              \
  (IDENTIFIER_NODE_CHECK (NODE)->base.u.bits.address_space)

/* In a RECORD_TYPE or UNION_TYPE, nonzero if any component is read-only.  */
#define C_TYPE_FIELDS_READONLY(TYPE)                                           \
  (LANG_TYPE_CLASS_CHECK (TYPE)->fields_readonly)

/* The tokens stored in the unparsed operand.  */

#define DEFPARSE_TOKENS(NODE)                                                  \
  (((struct tree_deferred_parse *) DEFERRED_PARSE_CHECK (NODE))->tokens)
#define DEFPARSE_INSTANTIATIONS(NODE)                                          \
  (((struct tree_deferred_parse *) DEFERRED_PARSE_CHECK (NODE))->instantiations)

#define DEFERRED_NOEXCEPT_PATTERN(NODE)                                        \
  (((struct tree_deferred_noexcept *) DEFERRED_NOEXCEPT_CHECK (NODE))->pattern)
#define DEFERRED_NOEXCEPT_ARGS(NODE)                                           \
  (((struct tree_deferred_noexcept *) DEFERRED_NOEXCEPT_CHECK (NODE))->args)
#define DEFERRED_NOEXCEPT_SPEC_P(NODE)                                         \
  ((NODE) && (TREE_PURPOSE (NODE))                                             \
   && (TREE_CODE (TREE_PURPOSE (NODE)) == DEFERRED_NOEXCEPT))
#define UNEVALUATED_NOEXCEPT_SPEC_P(NODE)                                      \
  (DEFERRED_NOEXCEPT_SPEC_P (NODE)                                             \
   && DEFERRED_NOEXCEPT_PATTERN (TREE_PURPOSE (NODE)) == NULL_TREE)
#define UNPARSED_NOEXCEPT_SPEC_P(NODE)                                         \
  ((NODE) && (TREE_PURPOSE (NODE))                                             \
   && (TREE_CODE (TREE_PURPOSE (NODE)) == DEFERRED_PARSE))

/* The condition associated with the static assertion.  This must be
   an integral constant expression.  */
#define STATIC_ASSERT_CONDITION(NODE)                                          \
  (((struct tree_static_assert *) STATIC_ASSERT_CHECK (NODE))->condition)

/* The message associated with the static assertion.  This must be a
   string constant, which will be emitted as an error message when the
   static assert condition is false.  */
#define STATIC_ASSERT_MESSAGE(NODE)                                            \
  (((struct tree_static_assert *) STATIC_ASSERT_CHECK (NODE))->message)

/* Source location information for a static assertion.  */
#define STATIC_ASSERT_SOURCE_LOCATION(NODE)                                    \
  (((struct tree_static_assert *) STATIC_ASSERT_CHECK (NODE))->location)

/* The types that we are processing.  */
#define TRAIT_EXPR_TYPE1(NODE)                                                 \
  (((struct tree_trait_expr *) TRAIT_EXPR_CHECK (NODE))->type1)

#define TRAIT_EXPR_TYPE2(NODE)                                                 \
  (((struct tree_trait_expr *) TRAIT_EXPR_CHECK (NODE))->type2)

/* The specific trait that we are processing.  */
#define TRAIT_EXPR_KIND(NODE)                                                  \
  (((struct tree_trait_expr *) TRAIT_EXPR_CHECK (NODE))->kind)

#define TRAIT_EXPR_LOCATION(NODE)                                              \
  (((struct tree_trait_expr *) TRAIT_EXPR_CHECK (NODE))->locus)

/* Identifiers used for lambda types are almost anonymous.  Use this
   spare flag to distinguish them (they also have the anonymous flag).  */
#define IDENTIFIER_LAMBDA_P(NODE)                                              \
  (IDENTIFIER_NODE_CHECK (NODE)->base.protected_flag)

/* Based off of TYPE_UNNAMED_P.  */
#define LAMBDA_TYPE_P(NODE)                                                    \
  (TREE_CODE (NODE) == RECORD_TYPE && TYPE_LINKAGE_IDENTIFIER (NODE)           \
   && IDENTIFIER_LAMBDA_P (TYPE_LINKAGE_IDENTIFIER (NODE)))

/* Test if FUNCTION_DECL is a lambda function.  */
#define LAMBDA_FUNCTION_P(FNDECL)                                              \
  (DECL_DECLARES_FUNCTION_P (FNDECL) && DECL_OVERLOADED_OPERATOR_P (FNDECL)    \
   && DECL_OVERLOADED_OPERATOR_IS (FNDECL, CALL_EXPR)                          \
   && LAMBDA_TYPE_P (CP_DECL_CONTEXT (FNDECL)))
/* The method of default capture, if any.  */
#define LAMBDA_EXPR_DEFAULT_CAPTURE_MODE(NODE)                                 \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->default_capture_mode)

/* The capture-list, including `this'.  Each capture is stored as a FIELD_DECL
 * so that the name, type, and field are all together, whether or not it has
 * been added to the lambda's class type.
   TREE_LIST:
     TREE_PURPOSE: The FIELD_DECL for this capture.
     TREE_VALUE: The initializer. This is part of a GNU extension.  */
#define LAMBDA_EXPR_CAPTURE_LIST(NODE)                                         \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->capture_list)

/* During parsing of the lambda-introducer, the node in the capture-list
   that holds the 'this' capture.  During parsing of the body, the
   capture proxy for that node.  */
#define LAMBDA_EXPR_THIS_CAPTURE(NODE)                                         \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->this_capture)

/* Predicate tracking whether `this' is in the effective capture set.  */
#define LAMBDA_EXPR_CAPTURES_THIS_P(NODE) LAMBDA_EXPR_THIS_CAPTURE (NODE)

/* Predicate tracking whether the lambda was declared 'mutable'.  */
#define LAMBDA_EXPR_MUTABLE_P(NODE) TREE_LANG_FLAG_1 (LAMBDA_EXPR_CHECK (NODE))

/* True iff uses of a const variable capture were optimized away.  */
#define LAMBDA_EXPR_CAPTURE_OPTIMIZED(NODE)                                    \
  TREE_LANG_FLAG_2 (LAMBDA_EXPR_CHECK (NODE))

/* True if this TREE_LIST in LAMBDA_EXPR_CAPTURE_LIST is for an explicit
   capture.  */
#define LAMBDA_CAPTURE_EXPLICIT_P(NODE)                                        \
  TREE_LANG_FLAG_0 (TREE_LIST_CHECK (NODE))

/* The source location of the lambda.  */
#define LAMBDA_EXPR_LOCATION(NODE)                                             \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->locus)

/* The mangling scope for the lambda: FUNCTION_DECL, PARM_DECL, VAR_DECL,
   FIELD_DECL or NULL_TREE.  If this is NULL_TREE, we have no linkage.  */
#define LAMBDA_EXPR_EXTRA_SCOPE(NODE)                                          \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->extra_scope)

/* If EXTRA_SCOPE, this is the number of the lambda within that scope.  */
#define LAMBDA_EXPR_DISCRIMINATOR(NODE)                                        \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->discriminator)

/* During parsing of the lambda, a vector of capture proxies which need
   to be pushed once we're done processing a nested lambda.  */
#define LAMBDA_EXPR_PENDING_PROXIES(NODE)                                      \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->pending_proxies)

/* If NODE was regenerated via tsubst_lambda_expr, this is a TEMPLATE_INFO
   whose TI_TEMPLATE is the immediate LAMBDA_EXPR from which NODE was
   regenerated, and TI_ARGS is the full set of template arguments used
   to regenerate NODE from the most general lambda.  */
#define LAMBDA_EXPR_REGEN_INFO(NODE)                                           \
  (((struct tree_lambda_expr *) LAMBDA_EXPR_CHECK (NODE))->regen_info)

/* The closure type of the lambda, which is also the type of the
   LAMBDA_EXPR.  */
#define LAMBDA_EXPR_CLOSURE(NODE) (TREE_TYPE (LAMBDA_EXPR_CHECK (NODE)))

/* Non-zero if this template specialization has access violations that
   should be rechecked when the function is instantiated outside argument
   deduction.  */
#define TINFO_HAS_ACCESS_ERRORS(NODE)                                          \
  (TREE_LANG_FLAG_0 (TEMPLATE_INFO_CHECK (NODE)))
#define FNDECL_HAS_ACCESS_ERRORS(NODE)                                         \
  (TINFO_HAS_ACCESS_ERRORS (DECL_TEMPLATE_INFO (NODE)))

/* Non-zero if this variable template specialization was specified using a
   template-id, so it's a partial or full specialization and not a definition
   of the member template of a particular class specialization.  */
#define TINFO_USED_TEMPLATE_ID(NODE)                                           \
  (TREE_LANG_FLAG_1 (TEMPLATE_INFO_CHECK (NODE)))

/* Access the expression describing the template constraints. This may be
   null if no constraints were introduced in the template parameter list,
   a requirements clause after the template parameter list, or constraints
   through a constrained-type-specifier.  */
#define CI_TEMPLATE_REQS(NODE)                                                 \
  check_constraint_info (check_nonnull (NODE))->template_reqs

/* Access the expression describing the trailing constraints. This is non-null
   for any implicit instantiation of a constrained declaration. For a
   templated declaration it is non-null only when a trailing requires-clause
   was specified.  */
#define CI_DECLARATOR_REQS(NODE)                                               \
  check_constraint_info (check_nonnull (NODE))->declarator_reqs

/* The computed associated constraint expression for a declaration.  */
#define CI_ASSOCIATED_CONSTRAINTS(NODE)                                        \
  check_constraint_info (check_nonnull (NODE))->associated_constr

/* Access the constraint-expression introduced by the requires-clause
   associate the template parameter list NODE.  */
#define TEMPLATE_PARMS_CONSTRAINTS(NODE) TREE_TYPE (TREE_LIST_CHECK (NODE))

/* Access the logical constraints on the template parameter declaration
   indicated by NODE.  */
#define TEMPLATE_PARM_CONSTRAINTS(NODE) TREE_TYPE (TREE_LIST_CHECK (NODE))

/* Non-zero if the noexcept is present in a compound requirement.  */
#define COMPOUND_REQ_NOEXCEPT_P(NODE)                                          \
  TREE_LANG_FLAG_0 (TREE_CHECK (NODE, COMPOUND_REQ))

/* A TREE_LIST whose TREE_VALUE is the constraints on the 'auto' placeholder
   type NODE, used in an argument deduction constraint.  The TREE_PURPOSE
   holds the set of template parameters that were in-scope when this 'auto'
   was formed.  */
#define PLACEHOLDER_TYPE_CONSTRAINTS_INFO(NODE)                                \
  DECL_SIZE_UNIT (TYPE_NAME (NODE))

/* The constraints on the 'auto' placeholder type NODE.  */
#define PLACEHOLDER_TYPE_CONSTRAINTS(NODE)                                     \
  (PLACEHOLDER_TYPE_CONSTRAINTS_INFO (NODE)                                    \
     ? TREE_VALUE (PLACEHOLDER_TYPE_CONSTRAINTS_INFO (NODE))                   \
     : NULL_TREE)

/* True if NODE is a constraint.  */
#define CONSTR_P(NODE)                                                         \
  (TREE_CODE (NODE) == ATOMIC_CONSTR || TREE_CODE (NODE) == CONJ_CONSTR        \
   || TREE_CODE (NODE) == DISJ_CONSTR)

/* Valid for any normalized constraint.  */
#define CONSTR_CHECK(NODE)                                                     \
  TREE_CHECK3 (NODE, ATOMIC_CONSTR, CONJ_CONSTR, DISJ_CONSTR)

/* The CONSTR_INFO stores normalization data for a constraint. It refers to
   the original expression and the expression or declaration
   from which the constraint was normalized.

   This is TREE_LIST whose TREE_PURPOSE is the original expression and whose
   TREE_VALUE is a list of contexts.  */
#define CONSTR_INFO(NODE) TREE_TYPE (CONSTR_CHECK (NODE))

/* The expression evaluated by the constraint.  */
#define CONSTR_EXPR(NODE) TREE_PURPOSE (CONSTR_INFO (NODE))

/* The expression or declaration from which this constraint was normalized.
   This is a TREE_LIST whose TREE_VALUE is either a template-id expression
   denoting a concept check or the declaration introducing the constraint.
   These are chained to other context objects.  */
#define CONSTR_CONTEXT(NODE) TREE_VALUE (CONSTR_INFO (NODE))

/* The parameter mapping for an atomic constraint. */
#define ATOMIC_CONSTR_MAP(NODE)                                                \
  TREE_OPERAND (TREE_CHECK (NODE, ATOMIC_CONSTR), 0)

/* Whether the parameter mapping of this atomic constraint
   is already instantiated with concrete template arguments.
   Used only in satisfy_atom and in the satisfaction cache.  */
#define ATOMIC_CONSTR_MAP_INSTANTIATED_P(NODE)                                 \
  TREE_LANG_FLAG_0 (ATOMIC_CONSTR_CHECK (NODE))

/* The expression of an atomic constraint. */
#define ATOMIC_CONSTR_EXPR(NODE) CONSTR_EXPR (ATOMIC_CONSTR_CHECK (NODE))

/* The concept of a concept check. */
#define CHECK_CONSTR_CONCEPT(NODE)                                             \
  TREE_OPERAND (TREE_CHECK (NODE, CHECK_CONSTR), 0)

/* The template arguments of a concept check. */
#define CHECK_CONSTR_ARGS(NODE)                                                \
  TREE_OPERAND (TREE_CHECK (NODE, CHECK_CONSTR), 1)

/* Whether a PARM_DECL represents a local parameter in a
   requires-expression.  */
#define CONSTRAINT_VAR_P(NODE) DECL_LANG_FLAG_2 (TREE_CHECK (NODE, PARM_DECL))

/* The concept constraining this constrained template-parameter.  */
#define CONSTRAINED_PARM_CONCEPT(NODE) DECL_SIZE_UNIT (TYPE_DECL_CHECK (NODE))
/* Any extra template arguments specified for a constrained
   template-parameter.  */
#define CONSTRAINED_PARM_EXTRA_ARGS(NODE) DECL_SIZE (TYPE_DECL_CHECK (NODE))
/* The first template parameter of CONSTRAINED_PARM_CONCEPT to be used as a
   prototype for the constrained parameter in finish_shorthand_constraint,
   attached for convenience.  */
#define CONSTRAINED_PARM_PROTOTYPE(NODE) DECL_INITIAL (TYPE_DECL_CHECK (NODE))

/* Module flags on FUNCTION,VAR,TYPE,CONCEPT or NAMESPACE
   A TEMPLATE_DECL holds them on the DECL_TEMPLATE_RESULT object --
   it's just not practical to keep them consistent.  */
#define DECL_MODULE_CHECK(NODE) TREE_NOT_CHECK (NODE, TEMPLATE_DECL)

/* In the purview of a module (including header unit).  */
#define DECL_MODULE_PURVIEW_P(N)                                               \
  (DECL_LANG_SPECIFIC (DECL_MODULE_CHECK (N))->u.base.module_purview_p)

/* True if the live version of the decl was imported.  */
#define DECL_MODULE_IMPORT_P(NODE)                                             \
  (DECL_LANG_SPECIFIC (DECL_MODULE_CHECK (NODE))->u.base.module_import_p)

/* True if this decl is in the entity hash & array.  This means that
   some variant was imported, even if DECL_MODULE_IMPORT_P is false.  */
#define DECL_MODULE_ENTITY_P(NODE)                                             \
  (DECL_LANG_SPECIFIC (DECL_MODULE_CHECK (NODE))->u.base.module_entity_p)

/* DECL that has attached decls for ODR-relatedness.  */
#define DECL_MODULE_ATTACHMENTS_P(NODE)                                        \
  (DECL_LANG_SPECIFIC (TREE_CHECK2 (NODE, FUNCTION_DECL, VAR_DECL))            \
     ->u.base.module_attached_p)

/* Whether this is an exported DECL.  Held on any decl that can appear
   at namespace scope (function, var, type, template, const or
   namespace).  templates copy from their template_result, consts have
   it for unscoped enums.  */
#define DECL_MODULE_EXPORT_P(NODE) TREE_LANG_FLAG_3 (NODE)

/* The list of local parameters introduced by this requires-expression,
   in the form of a chain of PARM_DECLs.  */
#define REQUIRES_EXPR_PARMS(NODE)                                              \
  TREE_OPERAND (TREE_CHECK (NODE, REQUIRES_EXPR), 0)

/* A TREE_LIST of the requirements for this requires-expression.
   The requirements are stored in lexical order within the TREE_VALUE
   of each TREE_LIST node.  The TREE_PURPOSE of each node is unused.  */
#define REQUIRES_EXPR_REQS(NODE)                                               \
  TREE_OPERAND (TREE_CHECK (NODE, REQUIRES_EXPR), 1)

/* Like PACK_EXPANSION_EXTRA_ARGS, for requires-expressions.  */
#define REQUIRES_EXPR_EXTRA_ARGS(NODE)                                         \
  TREE_OPERAND (TREE_CHECK (NODE, REQUIRES_EXPR), 2)

/* The current open namespace.  */

#define current_namespace scope_chain->old_namespace

/* The stack for namespaces of current declarations.  */

#define decl_namespace_list scope_chain->decl_ns_list

/* IDENTIFIER_NODE: name of current class */

#define current_class_name scope_chain->class_name

/* _TYPE: the type of the current class */

#define current_class_type scope_chain->class_type

/* When parsing a class definition, the access specifier most recently
   given by the user, or, if no access specifier was given, the
   default value appropriate for the kind of class (i.e., struct,
   class, or union).  */

#define current_access_specifier scope_chain->access_specifier

/* Pointer to the top of the language name stack.  */

#define current_lang_base scope_chain->lang_base
#define current_lang_name scope_chain->lang_name

/* When parsing a template declaration, a TREE_LIST represents the
   active template parameters.  Each node in the list represents one
   level of template parameters.  The innermost level is first in the
   list.  The depth of each level is stored as an INTEGER_CST in the
   TREE_PURPOSE of each node.  The parameters for that level are
   stored in the TREE_VALUE.  */

#define current_template_parms scope_chain->template_parms
#define current_template_depth                                                 \
  (current_template_parms ? TMPL_PARMS_DEPTH (current_template_parms) : 0)

#define processing_template_decl scope_chain->x_processing_template_decl
#define processing_specialization scope_chain->x_processing_specialization
#define processing_explicit_instantiation                                      \
  scope_chain->x_processing_explicit_instantiation

#define in_discarded_stmt scope_chain->discarded_stmt
#define in_consteval_if_p scope_chain->consteval_if_p

#define current_ref_temp_count scope_chain->ref_temp_count

/* The current C++-specific per-function global variables.  */

#define cp_function_chain (cfun->language)

/* In a constructor destructor, the point at which all derived class
   destroying/construction has been done.  I.e., just before a
   constructor returns, or before any base class destroying will be done
   in a destructor.  */

#define cdtor_label cp_function_chain->x_cdtor_label

/* When we're processing a member function, current_class_ptr is the
   PARM_DECL for the `this' pointer.  The current_class_ref is an
   expression for `*this'.  */

#define current_class_ptr                                                      \
  (*(cfun && cp_function_chain ? &cp_function_chain->x_current_class_ptr       \
			       : &scope_chain->x_current_class_ptr))
#define current_class_ref                                                      \
  (*(cfun && cp_function_chain ? &cp_function_chain->x_current_class_ref       \
			       : &scope_chain->x_current_class_ref))

/* The EH_SPEC_BLOCK for the exception-specifiers for the current
   function, if any.  */

#define current_eh_spec_block cp_function_chain->x_eh_spec_block

/* The `__in_chrg' parameter for the current function.  Only used for
   constructors and destructors.  */

#define current_in_charge_parm cp_function_chain->x_in_charge_parm

/* The `__vtt_parm' parameter for the current function.  Only used for
   constructors and destructors.  */

#define current_vtt_parm cp_function_chain->x_vtt_parm

/* A boolean flag to control whether we need to clean up the return value if a
   local destructor throws.  Only used in functions that return by value a
   class with a destructor.  Which 'tors don't, so we can use the same
   field as current_vtt_parm.  */

#define current_retval_sentinel current_vtt_parm

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement that specifies a return value is seen.  */

#define current_function_returns_value cp_function_chain->returns_value

/* Set to 0 at beginning of a function definition, set to 1 if
   a return statement with no argument is seen.  */

#define current_function_returns_null cp_function_chain->returns_null

/* Set to 0 at beginning of a function definition, set to 1 if
   a call to a noreturn function is seen.  */

#define current_function_returns_abnormally                                    \
  cp_function_chain->returns_abnormally

/* Set to 0 at beginning of a function definition, set to 1 if we see an
   obvious infinite loop.  This can have false positives and false
   negatives, so it should only be used as a heuristic.  */

#define current_function_infinite_loop cp_function_chain->infinite_loop

/* Nonzero if we are processing a base initializer.  Zero elsewhere.  */
#define in_base_initializer cp_function_chain->x_in_base_initializer

#define in_function_try_handler cp_function_chain->x_in_function_try_handler

/* Expression always returned from function, or error_mark_node
   otherwise, for use by the automatic named return value optimization.  */

#define current_function_return_value (cp_function_chain->x_return_value)

#define NON_ERROR(NODE) ((NODE) == error_mark_node ? NULL_TREE : (NODE))

#define STATEMENT_CODE_P(CODE) statement_code_p[(int) (CODE)]

/* Macros to make error reporting functions' lives easier.  */
#define TYPE_LINKAGE_IDENTIFIER(NODE)                                          \
  (TYPE_IDENTIFIER (TYPE_MAIN_VARIANT (NODE)))
#define TYPE_NAME_STRING(NODE) (IDENTIFIER_POINTER (TYPE_IDENTIFIER (NODE)))
#define TYPE_NAME_LENGTH(NODE) (IDENTIFIER_LENGTH (TYPE_IDENTIFIER (NODE)))

/* Any kind of anonymous type.  */
#define TYPE_ANON_P(NODE)                                                      \
  (TYPE_LINKAGE_IDENTIFIER (NODE)                                              \
   && IDENTIFIER_ANON_P (TYPE_LINKAGE_IDENTIFIER (NODE)))

/* Nonzero if NODE, a TYPE, has no name for linkage purposes.  */
#define TYPE_UNNAMED_P(NODE)                                                   \
  (TYPE_ANON_P (NODE) && !IDENTIFIER_LAMBDA_P (TYPE_LINKAGE_IDENTIFIER (NODE)))

/* The _DECL for this _TYPE.  */
#define TYPE_MAIN_DECL(NODE) (TYPE_STUB_DECL (TYPE_MAIN_VARIANT (NODE)))

/* Nonzero if T is a type that could resolve to any kind of concrete type
   at instantiation time.  */
#define WILDCARD_TYPE_P(T)                                                     \
  (TREE_CODE (T) == TEMPLATE_TYPE_PARM || TREE_CODE (T) == TYPENAME_TYPE       \
   || TREE_CODE (T) == TYPEOF_TYPE                                             \
   || TREE_CODE (T) == BOUND_TEMPLATE_TEMPLATE_PARM                            \
   || TREE_CODE (T) == DECLTYPE_TYPE                                           \
   || TREE_CODE (T) == DEPENDENT_OPERATOR_TYPE)

/* Nonzero if T is a class (or struct or union) type.  Also nonzero
   for template type parameters, typename types, and instantiated
   template template parameters.  Keep these checks in ascending code
   order.  */
#define MAYBE_CLASS_TYPE_P(T) (WILDCARD_TYPE_P (T) || CLASS_TYPE_P (T))

/* Set CLASS_TYPE_P for T to VAL.  T must be a class, struct, or
   union type.  */
#define SET_CLASS_TYPE_P(T, VAL)                                               \
  (TYPE_LANG_FLAG_5 (RECORD_OR_UNION_CHECK (T)) = (VAL))

/* Nonzero if T is a class type.  Zero for template type parameters,
   typename types, and so forth.  */
#define CLASS_TYPE_P(T)                                                        \
  (RECORD_OR_UNION_CODE_P (TREE_CODE (T)) && TYPE_LANG_FLAG_5 (T))

/* Nonzero if T is a class type but not a union.  */
#define NON_UNION_CLASS_TYPE_P(T)                                              \
  (TREE_CODE (T) == RECORD_TYPE && TYPE_LANG_FLAG_5 (T))

/* Keep these checks in ascending code order.  */
#define RECORD_OR_UNION_CODE_P(T) ((T) == RECORD_TYPE || (T) == UNION_TYPE)
#define OVERLOAD_TYPE_P(T) (CLASS_TYPE_P (T) || TREE_CODE (T) == ENUMERAL_TYPE)

/* True if this type is dependent.  This predicate is only valid if
   TYPE_DEPENDENT_P_VALID is true.  */
#define TYPE_DEPENDENT_P(NODE) TYPE_LANG_FLAG_0 (NODE)

/* True if dependent_type_p has been called for this type, with the
   result that TYPE_DEPENDENT_P is valid.  */
#define TYPE_DEPENDENT_P_VALID(NODE) TYPE_LANG_FLAG_6 (NODE)

/* Nonzero if this type is const-qualified.  */
#define CP_TYPE_CONST_P(NODE) ((cp_type_quals (NODE) & TYPE_QUAL_CONST) != 0)

/* Nonzero if this type is volatile-qualified.  */
#define CP_TYPE_VOLATILE_P(NODE)                                               \
  ((cp_type_quals (NODE) & TYPE_QUAL_VOLATILE) != 0)

/* Nonzero if this type is restrict-qualified.  */
#define CP_TYPE_RESTRICT_P(NODE)                                               \
  ((cp_type_quals (NODE) & TYPE_QUAL_RESTRICT) != 0)

/* Nonzero if this type is const-qualified, but not
   volatile-qualified.  Other qualifiers are ignored.  This macro is
   used to test whether or not it is OK to bind an rvalue to a
   reference.  */
#define CP_TYPE_CONST_NON_VOLATILE_P(NODE)                                     \
  ((cp_type_quals (NODE) & (TYPE_QUAL_CONST | TYPE_QUAL_VOLATILE))             \
   == TYPE_QUAL_CONST)

#define FUNCTION_ARG_CHAIN(NODE) TREE_CHAIN (TYPE_ARG_TYPES (TREE_TYPE (NODE)))

/* Given a FUNCTION_DECL, returns the first TREE_LIST out of TYPE_ARG_TYPES
   which refers to a user-written parameter.  */
#define FUNCTION_FIRST_USER_PARMTYPE(NODE)                                     \
  skip_artificial_parms_for ((NODE), TYPE_ARG_TYPES (TREE_TYPE (NODE)))

/* Similarly, but for DECL_ARGUMENTS.  */
#define FUNCTION_FIRST_USER_PARM(NODE)                                         \
  skip_artificial_parms_for ((NODE), DECL_ARGUMENTS (NODE))

/* Nonzero iff TYPE is derived from PARENT. Ignores accessibility and
   ambiguity issues.  */
#define DERIVED_FROM_P(PARENT, TYPE)                                           \
  (lookup_base ((TYPE), (PARENT), ba_any, NULL, tf_none) != NULL_TREE)

/* Gives the visibility specification for a class type.  */
#define CLASSTYPE_VISIBILITY(TYPE) DECL_VISIBILITY (TYPE_MAIN_DECL (TYPE))
#define CLASSTYPE_VISIBILITY_SPECIFIED(TYPE)                                   \
  DECL_VISIBILITY_SPECIFIED (TYPE_MAIN_DECL (TYPE))
/* We used to have a variant type for lang_type.  Keep the name of the
   checking accessor for the sole survivor.  */
#define LANG_TYPE_CLASS_CHECK(NODE) (TYPE_LANG_SPECIFIC (NODE))

/* Nonzero for _CLASSTYPE means that operator delete is defined.  */
#define TYPE_GETS_DELETE(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->gets_delete)
#define TYPE_GETS_REG_DELETE(NODE) (TYPE_GETS_DELETE (NODE) & 1)
#define TYPE_GETS_VEC_DELETE(NODE) (TYPE_GETS_DELETE (NODE) & 2)

/* Nonzero if `new NODE[x]' should cause the allocation of extra
   storage to indicate how many array elements are in use.  */
#define TYPE_VEC_NEW_USES_COOKIE(NODE)                                         \
  (CLASS_TYPE_P (NODE) && LANG_TYPE_CLASS_CHECK (NODE)->vec_new_uses_cookie)

/* Nonzero means that this _CLASSTYPE node defines ways of converting
   itself to other types.  */
#define TYPE_HAS_CONVERSION(NODE)                                              \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_type_conversion)

/* Nonzero means that NODE (a class type) has a default constructor --
   but that it has not yet been declared.  */
#define CLASSTYPE_LAZY_DEFAULT_CTOR(NODE)                                      \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_default_ctor)

/* Nonzero means that NODE (a class type) has a copy constructor --
   but that it has not yet been declared.  */
#define CLASSTYPE_LAZY_COPY_CTOR(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_copy_ctor)

/* Nonzero means that NODE (a class type) has a move constructor --
   but that it has not yet been declared.  */
#define CLASSTYPE_LAZY_MOVE_CTOR(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_move_ctor)

/* Nonzero means that NODE (a class type) has an assignment operator
   -- but that it has not yet been declared.  */
#define CLASSTYPE_LAZY_COPY_ASSIGN(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_copy_assign)

/* Nonzero means that NODE (a class type) has an assignment operator
   -- but that it has not yet been declared.  */
#define CLASSTYPE_LAZY_MOVE_ASSIGN(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_move_assign)

/* Nonzero means that NODE (a class type) has a destructor -- but that
   it has not yet been declared.  */
#define CLASSTYPE_LAZY_DESTRUCTOR(NODE)                                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->lazy_destructor)

/* Nonzero means that NODE (a class type) is final */
#define CLASSTYPE_FINAL(NODE) TYPE_FINAL_P (NODE)

/* Nonzero means that this _CLASSTYPE node overloads operator=(X&).  */
#define TYPE_HAS_COPY_ASSIGN(NODE)                                             \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_copy_assign)

/* True iff the class type NODE has an "operator =" whose parameter
   has a parameter of type "const X&".  */
#define TYPE_HAS_CONST_COPY_ASSIGN(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_const_copy_assign)

/* Nonzero means that this _CLASSTYPE node has an X(X&) constructor.  */
#define TYPE_HAS_COPY_CTOR(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->has_copy_ctor)
#define TYPE_HAS_CONST_COPY_CTOR(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_const_copy_ctor)

/* Nonzero if this class has an X(initializer_list<T>) constructor.  */
#define TYPE_HAS_LIST_CTOR(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->has_list_ctor)

/* Nonzero if this class has a constexpr constructor other than a copy/move
   constructor.  Note that a class can have constexpr constructors for
   static initialization even if it isn't a literal class.  */
#define TYPE_HAS_CONSTEXPR_CTOR(NODE)                                          \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_constexpr_ctor)

/* Nonzero if this class defines an overloaded operator new.  (An
   operator new [] doesn't count.)  */
#define TYPE_HAS_NEW_OPERATOR(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->has_new)

/* Nonzero if this class defines an overloaded operator new[].  */
#define TYPE_HAS_ARRAY_NEW_OPERATOR(NODE)                                      \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_array_new)

/* Nonzero means that this type is being defined.  I.e., the left brace
   starting the definition of this type has been seen.  */
#define TYPE_BEING_DEFINED(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->being_defined)

/* Nonzero means that this type is either complete or being defined, so we
   can do lookup in it.  */
#define COMPLETE_OR_OPEN_TYPE_P(NODE)                                          \
  (COMPLETE_TYPE_P (NODE) || (CLASS_TYPE_P (NODE) && TYPE_BEING_DEFINED (NODE)))

/* Mark bits for repeated base checks.  */
#define TYPE_MARKED_P(NODE) TREE_LANG_FLAG_6 (TYPE_CHECK (NODE))

/* Nonzero if the class NODE has multiple paths to the same (virtual)
   base object.  */
#define CLASSTYPE_DIAMOND_SHAPED_P(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->diamond_shaped)

/* Nonzero if the class NODE has multiple instances of the same base
   type.  */
#define CLASSTYPE_REPEATED_BASE_P(NODE)                                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->repeated_base)

/* The member function with which the vtable will be emitted:
   the first noninline non-pure-virtual member function.  NULL_TREE
   if there is no key function or if this is a class template */
#define CLASSTYPE_KEY_METHOD(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->key_method)

/* Vector of members.  During definition, it is unordered and only
   member functions are present.  After completion it is sorted and
   contains both member functions and non-functions.  STAT_HACK is
   involved to preserve oneslot per name invariant.  */
#define CLASSTYPE_MEMBER_VEC(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->members)

/* For class templates, this is a TREE_LIST of all member data,
   functions, types, and friends in the order of declaration.
   The TREE_PURPOSE of each TREE_LIST is NULL_TREE for a friend,
   and the RECORD_TYPE for the class template otherwise.  */
#define CLASSTYPE_DECL_LIST(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->decl_list)

/* A FUNCTION_DECL or OVERLOAD for the constructors for NODE.  These
   are the constructors that take an in-charge parameter.  */
#define CLASSTYPE_CONSTRUCTORS(NODE)                                           \
  (get_class_binding_direct (NODE, ctor_identifier))

/* A FUNCTION_DECL for the destructor for NODE.  This is the
   destructors that take an in-charge parameter.  If
   CLASSTYPE_LAZY_DESTRUCTOR is true, then this entry will be NULL
   until the destructor is created with lazily_declare_fn.  */
#define CLASSTYPE_DESTRUCTOR(NODE)                                             \
  (get_class_binding_direct (NODE, dtor_identifier))

/* Nonzero if NODE has a primary base class, i.e., a base class with
   which it shares the virtual function table pointer.  */
#define CLASSTYPE_HAS_PRIMARY_BASE_P(NODE)                                     \
  (CLASSTYPE_PRIMARY_BINFO (NODE) != NULL_TREE)

/* If non-NULL, this is the binfo for the primary base class, i.e.,
   the base class which contains the virtual function table pointer
   for this class.  */
#define CLASSTYPE_PRIMARY_BINFO(NODE)                                          \
  (LANG_TYPE_CLASS_CHECK (NODE)->primary_base)

/* A vector of BINFOs for the direct and indirect virtual base classes
   that this type uses in a post-order depth-first left-to-right
   order.  (In other words, these bases appear in the order that they
   should be initialized.)  */
#define CLASSTYPE_VBASECLASSES(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->vbases)

/* The type corresponding to NODE when NODE is used as a base class,
   i.e., NODE without virtual base classes or tail padding.  */
#define CLASSTYPE_AS_BASE(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->as_base)

/* True iff NODE is the CLASSTYPE_AS_BASE version of some type.  */
#define IS_FAKE_BASE_TYPE(NODE)                                                \
  (TREE_CODE (NODE) == RECORD_TYPE && TYPE_CONTEXT (NODE)                      \
   && CLASS_TYPE_P (TYPE_CONTEXT (NODE))                                       \
   && CLASSTYPE_AS_BASE (TYPE_CONTEXT (NODE)) == (NODE))

/* These are the size and alignment of the type without its virtual
   base classes, for when we use this type as a base itself.  */
#define CLASSTYPE_SIZE(NODE) TYPE_SIZE (CLASSTYPE_AS_BASE (NODE))
#define CLASSTYPE_SIZE_UNIT(NODE) TYPE_SIZE_UNIT (CLASSTYPE_AS_BASE (NODE))
#define CLASSTYPE_ALIGN(NODE) TYPE_ALIGN (CLASSTYPE_AS_BASE (NODE))
#define CLASSTYPE_USER_ALIGN(NODE) TYPE_USER_ALIGN (CLASSTYPE_AS_BASE (NODE))

/* The alignment of NODE, without its virtual bases, in bytes.  */
#define CLASSTYPE_ALIGN_UNIT(NODE) (CLASSTYPE_ALIGN (NODE) / BITS_PER_UNIT)

/* A vec<tree> of virtual functions which cannot be inherited by
   derived classes.  When deriving from this type, the derived
   class must provide its own definition for each of these functions.  */
#define CLASSTYPE_PURE_VIRTUALS(NODE)                                          \
  (LANG_TYPE_CLASS_CHECK (NODE)->pure_virtuals)

/* Nonzero means that this type is an abstract class type.  */
#define ABSTRACT_CLASS_TYPE_P(NODE)                                            \
  (CLASS_TYPE_P (NODE) && CLASSTYPE_PURE_VIRTUALS (NODE))

/* Nonzero means that this type has an X() constructor.  */
#define TYPE_HAS_DEFAULT_CONSTRUCTOR(NODE)                                     \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_default_ctor)

/* Nonzero means that this type contains a mutable member.  */
#define CLASSTYPE_HAS_MUTABLE(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->has_mutable)
#define TYPE_HAS_MUTABLE_P(NODE) (cp_has_mutable_p (NODE))

/* Nonzero means that this class type is not POD for the purpose of layout
   (as defined in the ABI).  This is different from the language's POD.  */
#define CLASSTYPE_NON_LAYOUT_POD_P(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->non_pod_class)

/* Nonzero means that this class type is a non-standard-layout class.  */
#define CLASSTYPE_NON_STD_LAYOUT(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->non_std_layout)

/* Nonzero means that this class type does have unique object
   representations.  */
#define CLASSTYPE_UNIQUE_OBJ_REPRESENTATIONS(NODE)                             \
  (LANG_TYPE_CLASS_CHECK (NODE)->unique_obj_representations)

/* Nonzero means that this class type has
   CLASSTYPE_UNIQUE_OBJ_REPRESENTATIONS computed.  */
#define CLASSTYPE_UNIQUE_OBJ_REPRESENTATIONS_SET(NODE)                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->unique_obj_representations_set)

/* Nonzero means that this class contains pod types whose default
   initialization is not a zero initialization (namely, pointers to
   data members).  */
#define CLASSTYPE_NON_ZERO_INIT_P(NODE)                                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->non_zero_init)

/* Nonzero if this class is "empty" in the sense of the C++ ABI.  */
#define CLASSTYPE_EMPTY_P(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->empty_p)

/* Nonzero if this class is "nearly empty", i.e., contains only a
   virtual function table pointer.  */
#define CLASSTYPE_NEARLY_EMPTY_P(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->nearly_empty_p)

/* Nonzero if this class contains an empty subobject.  */
#define CLASSTYPE_CONTAINS_EMPTY_CLASS_P(NODE)                                 \
  (LANG_TYPE_CLASS_CHECK (NODE)->contains_empty_class_p)

/* A list of class types of which this type is a friend.  The
   TREE_VALUE is normally a TYPE, but will be a TEMPLATE_DECL in the
   case of a template friend.  */
#define CLASSTYPE_FRIEND_CLASSES(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->friend_classes)

/* A list of the classes which grant friendship to this class.  */
#define CLASSTYPE_BEFRIENDING_CLASSES(NODE)                                    \
  (LANG_TYPE_CLASS_CHECK (NODE)->befriending_classes)

/* The associated LAMBDA_EXPR that made this class.  */
#define CLASSTYPE_LAMBDA_EXPR(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->lambda_expr)
/* The extra mangling scope for this closure type.  */
#define LAMBDA_TYPE_EXTRA_SCOPE(NODE)                                          \
  (LAMBDA_EXPR_EXTRA_SCOPE (CLASSTYPE_LAMBDA_EXPR (NODE)))

/* Say whether this node was declared as a "class" or a "struct".  */
#define CLASSTYPE_DECLARED_CLASS(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->declared_class)

/* Nonzero if this class has const members
   which have no specified initialization.  */
#define CLASSTYPE_READONLY_FIELDS_NEED_INIT(NODE)                              \
  (TYPE_LANG_SPECIFIC (NODE) ? LANG_TYPE_CLASS_CHECK (NODE)->const_needs_init  \
			     : 0)
#define SET_CLASSTYPE_READONLY_FIELDS_NEED_INIT(NODE, VALUE)                   \
  (LANG_TYPE_CLASS_CHECK (NODE)->const_needs_init = (VALUE))

/* Nonzero if this class has ref members
   which have no specified initialization.  */
#define CLASSTYPE_REF_FIELDS_NEED_INIT(NODE)                                   \
  (TYPE_LANG_SPECIFIC (NODE) ? LANG_TYPE_CLASS_CHECK (NODE)->ref_needs_init : 0)
#define SET_CLASSTYPE_REF_FIELDS_NEED_INIT(NODE, VALUE)                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->ref_needs_init = (VALUE))

/* Nonzero if this class is included from a header file which employs
   `#pragma interface', and it is not included in its implementation file.  */
#define CLASSTYPE_INTERFACE_ONLY(NODE)                                         \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_only)

/* True if we have already determined whether or not vtables, VTTs,
   typeinfo, and other similar per-class data should be emitted in
   this translation unit.  This flag does not indicate whether or not
   these items should be emitted; it only indicates that we know one
   way or the other.  */
#define CLASSTYPE_INTERFACE_KNOWN(NODE)                                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_unknown == 0)
/* The opposite of CLASSTYPE_INTERFACE_KNOWN.  */
#define CLASSTYPE_INTERFACE_UNKNOWN(NODE)                                      \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_unknown)

#define SET_CLASSTYPE_INTERFACE_UNKNOWN_X(NODE, X)                             \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_unknown = !!(X))
#define SET_CLASSTYPE_INTERFACE_UNKNOWN(NODE)                                  \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_unknown = 1)
#define SET_CLASSTYPE_INTERFACE_KNOWN(NODE)                                    \
  (LANG_TYPE_CLASS_CHECK (NODE)->interface_unknown = 0)

/* Nonzero if a _DECL node requires us to output debug info for this class.  */
#define CLASSTYPE_DEBUG_REQUESTED(NODE)                                        \
  (LANG_TYPE_CLASS_CHECK (NODE)->debug_requested)

/* True if we saw errors while instantiating this class.  */
#define CLASSTYPE_ERRONEOUS(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->erroneous)

/* True if this class is non-layout-POD only because it was not an aggregate
   before C++14.  If we run out of bits in lang_type, this could be replaced
   with a hash_set only filled in when abi_version_crosses (17).  */
#define CLASSTYPE_NON_POD_AGGREGATE(NODE)                                      \
  (LANG_TYPE_CLASS_CHECK (NODE)->non_pod_aggregate)

/* Additional macros for inheritance information.  */

/* Nonzero means that this class is on a path leading to a new vtable.  */
#define BINFO_VTABLE_PATH_MARKED(NODE) BINFO_FLAG_1 (NODE)

/* Nonzero means B (a BINFO) has its own vtable.  Any copies will not
   have this flag set.  */
#define BINFO_NEW_VTABLE_MARKED(B) (BINFO_FLAG_2 (B))

/* Compare a BINFO_TYPE with another type for equality.  For a binfo,
   this is functionally equivalent to using same_type_p, but
   measurably faster.  At least one of the arguments must be a
   BINFO_TYPE.  The other can be a BINFO_TYPE or a regular type.  If
   BINFO_TYPE(T) ever stops being the main variant of the class the
   binfo is for, this macro must change.  */
#define SAME_BINFO_TYPE_P(A, B) ((A) == (B))

/* Any subobject that needs a new vtable must have a vptr and must not
   be a non-virtual primary base (since it would then use the vtable from a
   derived class and never become non-primary.)  */
#define SET_BINFO_NEW_VTABLE_MARKED(B)                                         \
  (BINFO_NEW_VTABLE_MARKED (B) = 1,                                            \
   gcc_assert (!BINFO_PRIMARY_P (B) || BINFO_VIRTUAL_P (B)),                   \
   gcc_assert (TYPE_VFIELD (BINFO_TYPE (B))))

/* Nonzero if this binfo is for a dependent base - one that should not
   be searched.  */
#define BINFO_DEPENDENT_BASE_P(NODE) BINFO_FLAG_3 (NODE)

/* Nonzero if this binfo has lost its primary base binfo (because that
   is a nearly-empty virtual base that has been taken by some other
   base in the complete hierarchy.  */
#define BINFO_LOST_PRIMARY_P(NODE) BINFO_FLAG_4 (NODE)

/* Nonzero if this BINFO is a primary base class.  */
#define BINFO_PRIMARY_P(NODE) BINFO_FLAG_5 (NODE)

/* A vec<tree_pair_s> of the vcall indices associated with the class
   NODE.  The PURPOSE of each element is a FUNCTION_DECL for a virtual
   function.  The VALUE is the index into the virtual table where the
   vcall offset for that function is stored, when NODE is a virtual
   base.  */
#define CLASSTYPE_VCALL_INDICES(NODE)                                          \
  (LANG_TYPE_CLASS_CHECK (NODE)->vcall_indices)

/* The various vtables for the class NODE.  The primary vtable will be
   first, followed by the construction vtables and VTT, if any.  */
#define CLASSTYPE_VTABLES(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->vtables)

/* The std::type_info variable representing this class, or NULL if no
   such variable has been created.  This field is only set for the
   TYPE_MAIN_VARIANT of the class.  */
#define CLASSTYPE_TYPEINFO_VAR(NODE)                                           \
  (LANG_TYPE_CLASS_CHECK (NODE)->typeinfo_var)

/* Accessor macros for the BINFO_VIRTUALS list.  */

/* The number of bytes by which to adjust the `this' pointer when
   calling this virtual function.  Subtract this value from the this
   pointer. Always non-NULL, might be constant zero though.  */
#define BV_DELTA(NODE) (TREE_PURPOSE (NODE))

/* If non-NULL, the vtable index at which to find the vcall offset
   when calling this virtual function.  Add the value at that vtable
   index to the this pointer.  */
#define BV_VCALL_INDEX(NODE) (TREE_TYPE (NODE))

/* The function to call.  */
#define BV_FN(NODE) (TREE_VALUE (NODE))

/* Whether or not this entry is for a lost primary virtual base.  */
#define BV_LOST_PRIMARY(NODE) (TREE_LANG_FLAG_0 (NODE))

/* For FUNCTION_TYPE or METHOD_TYPE, a list of the exceptions that
   this type can raise.  Each TREE_VALUE is a _TYPE.  The TREE_VALUE
   will be NULL_TREE to indicate a throw specification of `()', or
   no exceptions allowed.  For a noexcept specification, TREE_VALUE
   is NULL_TREE and TREE_PURPOSE is the constant-expression.  For
   a deferred noexcept-specification, TREE_PURPOSE is a DEFERRED_NOEXCEPT
   (for templates) or an OVERLOAD list of functions (for implicitly
   declared functions).  */
#define TYPE_RAISES_EXCEPTIONS(NODE)                                           \
  TYPE_LANG_SLOT_1 (FUNC_OR_METHOD_CHECK (NODE))

/* For FUNCTION_TYPE or METHOD_TYPE, return 1 iff it is declared `throw()'
   or noexcept(true).  */
#define TYPE_NOTHROW_P(NODE) nothrow_spec_p (TYPE_RAISES_EXCEPTIONS (NODE))

/* For FUNCTION_TYPE or METHOD_TYPE, true if NODE is noexcept.  This is the
   case for things declared noexcept(true) and, with -fnothrow-opt, for
   throw() functions.  */
#define TYPE_NOEXCEPT_P(NODE) type_noexcept_p (NODE)

/* The binding level associated with the namespace.  */
#define NAMESPACE_LEVEL(NODE) (LANG_DECL_NS_CHECK (NODE)->level)

/* True for DECL codes which have template info and access.  */
#define LANG_DECL_HAS_MIN(NODE)                                                \
  (VAR_OR_FUNCTION_DECL_P (NODE) || TREE_CODE (NODE) == FIELD_DECL             \
   || TREE_CODE (NODE) == CONST_DECL || TREE_CODE (NODE) == TYPE_DECL          \
   || TREE_CODE (NODE) == TEMPLATE_DECL || TREE_CODE (NODE) == USING_DECL      \
   || TREE_CODE (NODE) == CONCEPT_DECL)

/* Looks through a template (if present) to find what it declares.  */
#define STRIP_TEMPLATE(NODE)                                                   \
  (TREE_CODE (NODE) == TEMPLATE_DECL ? DECL_TEMPLATE_RESULT (NODE) : NODE)

#if defined ENABLE_TREE_CHECKING && (GCC_VERSION >= 2007)

#define LANG_DECL_MIN_CHECK(NODE)                                              \
  __extension__({                                                              \
    struct lang_decl *lt = DECL_LANG_SPECIFIC (NODE);                          \
    if (!LANG_DECL_HAS_MIN (NODE))                                             \
      lang_check_failed (__FILE__, __LINE__, __FUNCTION__);                    \
    &lt->u.min;                                                                \
  })

/* We want to be able to check DECL_CONSTRUCTOR_P and such on a function
   template, not just on a FUNCTION_DECL.  So when looking for things in
   lang_decl_fn, look down through a TEMPLATE_DECL into its result.  */
#define LANG_DECL_FN_CHECK(NODE)                                               \
  __extension__({                                                              \
    struct lang_decl *lt = DECL_LANG_SPECIFIC (STRIP_TEMPLATE (NODE));         \
    if (!DECL_DECLARES_FUNCTION_P (NODE) || lt->u.base.selector != lds_fn)     \
      lang_check_failed (__FILE__, __LINE__, __FUNCTION__);                    \
    &lt->u.fn;                                                                 \
  })

#define LANG_DECL_NS_CHECK(NODE)                                               \
  __extension__({                                                              \
    struct lang_decl *lt = DECL_LANG_SPECIFIC (NODE);                          \
    if (TREE_CODE (NODE) != NAMESPACE_DECL || lt->u.base.selector != lds_ns)   \
      lang_check_failed (__FILE__, __LINE__, __FUNCTION__);                    \
    &lt->u.ns;                                                                 \
  })

#define LANG_DECL_PARM_CHECK(NODE)                                             \
  __extension__({                                                              \
    struct lang_decl *lt = DECL_LANG_SPECIFIC (NODE);                          \
    if (TREE_CODE (NODE) != PARM_DECL || lt->u.base.selector != lds_parm)      \
      lang_check_failed (__FILE__, __LINE__, __FUNCTION__);                    \
    &lt->u.parm;                                                               \
  })

#define LANG_DECL_DECOMP_CHECK(NODE)                                           \
  __extension__({                                                              \
    struct lang_decl *lt = DECL_LANG_SPECIFIC (NODE);                          \
    if (!VAR_P (NODE) || lt->u.base.selector != lds_decomp)                    \
      lang_check_failed (__FILE__, __LINE__, __FUNCTION__);                    \
    &lt->u.decomp;                                                             \
  })

#else

#define LANG_DECL_MIN_CHECK(NODE) (&DECL_LANG_SPECIFIC (NODE)->u.min)

#define LANG_DECL_FN_CHECK(NODE)                                               \
  (&DECL_LANG_SPECIFIC (STRIP_TEMPLATE (NODE))->u.fn)

#define LANG_DECL_NS_CHECK(NODE) (&DECL_LANG_SPECIFIC (NODE)->u.ns)

#define LANG_DECL_PARM_CHECK(NODE) (&DECL_LANG_SPECIFIC (NODE)->u.parm)

#define LANG_DECL_DECOMP_CHECK(NODE) (&DECL_LANG_SPECIFIC (NODE)->u.decomp)

#endif /* ENABLE_TREE_CHECKING */

/* For a FUNCTION_DECL or a VAR_DECL, the language linkage for the
   declaration.  Some entities (like a member function in a local
   class, or a local variable) do not have linkage at all, and this
   macro should not be used in those cases.

   Implementation note: A FUNCTION_DECL without DECL_LANG_SPECIFIC was
   created by language-independent code, and has C linkage.  Most
   VAR_DECLs have C++ linkage, and do not have DECL_LANG_SPECIFIC, but
   we do create DECL_LANG_SPECIFIC for variables with non-C++ linkage.  */
#define DECL_LANGUAGE(NODE)                                                    \
  (DECL_LANG_SPECIFIC (NODE)                                                   \
     ? DECL_LANG_SPECIFIC (NODE)->u.base.language                              \
     : (TREE_CODE (NODE) == FUNCTION_DECL ? lang_c : lang_cplusplus))

/* Set the language linkage for NODE to LANGUAGE.  */
#define SET_DECL_LANGUAGE(NODE, LANGUAGE)                                      \
  (DECL_LANG_SPECIFIC (NODE)->u.base.language = (LANGUAGE))

/* For FUNCTION_DECLs and TEMPLATE_DECLs: nonzero means that this function
   is a constructor.  */
#define DECL_CONSTRUCTOR_P(NODE) DECL_CXX_CONSTRUCTOR_P (STRIP_TEMPLATE (NODE))

/* Nonzero if NODE (a FUNCTION_DECL) is a constructor for a complete
   object.  */
#define DECL_COMPLETE_CONSTRUCTOR_P(NODE)                                      \
  (DECL_NAME (NODE) == complete_ctor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a constructor for a base
   object.  */
#define DECL_BASE_CONSTRUCTOR_P(NODE) (DECL_NAME (NODE) == base_ctor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a constructor, but not either the
   specialized in-charge constructor or the specialized not-in-charge
   constructor.  */
#define DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P(NODE)                               \
  (DECL_NAME (NODE) == ctor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a copy constructor.  */
#define DECL_COPY_CONSTRUCTOR_P(NODE)                                          \
  (DECL_CONSTRUCTOR_P (NODE) && copy_fn_p (NODE) > 0)

/* Nonzero if NODE (a FUNCTION_DECL) is a move constructor.  */
#define DECL_MOVE_CONSTRUCTOR_P(NODE)                                          \
  (DECL_CONSTRUCTOR_P (NODE) && move_fn_p (NODE))

/* Nonzero if NODE (a FUNCTION_DECL or TEMPLATE_DECL)
   is a destructor.  */
#define DECL_DESTRUCTOR_P(NODE) DECL_CXX_DESTRUCTOR_P (STRIP_TEMPLATE (NODE))

/* Nonzero if NODE (a FUNCTION_DECL) is a destructor, but not the
   specialized in-charge constructor, in-charge deleting constructor,
   or the base destructor.  */
#define DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P(NODE)                                \
  (DECL_NAME (NODE) == dtor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a destructor for a complete
   object.  */
#define DECL_COMPLETE_DESTRUCTOR_P(NODE)                                       \
  (DECL_NAME (NODE) == complete_dtor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a destructor for a base
   object.  */
#define DECL_BASE_DESTRUCTOR_P(NODE) (DECL_NAME (NODE) == base_dtor_identifier)

/* Nonzero if NODE (a FUNCTION_DECL) is a destructor for a complete
   object that deletes the object after it has been destroyed.  */
#define DECL_DELETING_DESTRUCTOR_P(NODE)                                       \
  (DECL_NAME (NODE) == deleting_dtor_identifier)

/* Nonzero if either DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P or
   DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P is true of NODE.  */
#define DECL_MAYBE_IN_CHARGE_CDTOR_P(NODE)                                     \
  (DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (NODE)                                   \
   || DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (NODE))

/* Nonzero if NODE (a _DECL) is a cloned constructor or
   destructor.  */
#define DECL_CLONED_FUNCTION_P(NODE)                                           \
  (DECL_NAME (NODE) && IDENTIFIER_CDTOR_P (DECL_NAME (NODE))                   \
   && !DECL_MAYBE_IN_CHARGE_CDTOR_P (NODE))

/* If DECL_CLONED_FUNCTION_P holds, this is the function that was
   cloned.  */
#define DECL_CLONED_FUNCTION(NODE)                                             \
  (DECL_LANG_SPECIFIC (FUNCTION_DECL_CHECK (NODE))->u.fn.u5.cloned_function)

/* Perform an action for each clone of FN, if FN is a function with
   clones.  This macro should be used like:

      FOR_EACH_CLONE (clone, fn)
	{ ... }

  */
#define FOR_EACH_CLONE(CLONE, FN)                                              \
  if (!(TREE_CODE (FN) == FUNCTION_DECL && DECL_MAYBE_IN_CHARGE_CDTOR_P (FN))) \
    ;                                                                          \
  else                                                                         \
    for (CLONE = DECL_CHAIN (FN); CLONE && DECL_CLONED_FUNCTION_P (CLONE);     \
	 CLONE = DECL_CHAIN (CLONE))

/* Nonzero if NODE has DECL_DISCRIMINATOR and not DECL_ACCESS.  */
#define DECL_DISCRIMINATOR_P(NODE)                                             \
  (((TREE_CODE (NODE) == VAR_DECL && TREE_STATIC (NODE))                       \
    || DECL_IMPLICIT_TYPEDEF_P (NODE))                                         \
   && DECL_FUNCTION_SCOPE_P (NODE))

/* Discriminator for name mangling.  */
#define DECL_DISCRIMINATOR(NODE) (LANG_DECL_MIN_CHECK (NODE)->access)

/* The index of a user-declared parameter in its function, starting at 1.
   All artificial parameters will have index 0.  */
#define DECL_PARM_INDEX(NODE) (LANG_DECL_PARM_CHECK (NODE)->index)

/* The level of a user-declared parameter in its function, starting at 1.
   A parameter of the function will have level 1; a parameter of the first
   nested function declarator (i.e. t in void f (void (*p)(T t))) will have
   level 2.  */
#define DECL_PARM_LEVEL(NODE) (LANG_DECL_PARM_CHECK (NODE)->level)

/* Nonzero if the VTT parm has been added to NODE.  */
#define DECL_HAS_VTT_PARM_P(NODE) (LANG_DECL_FN_CHECK (NODE)->has_vtt_parm_p)

/* Nonzero if NODE is a user-defined conversion operator.  */
#define DECL_CONV_FN_P(NODE) IDENTIFIER_CONV_OP_P (DECL_NAME (NODE))

/* The type to which conversion operator FN converts to.   */
#define DECL_CONV_FN_TYPE(FN)                                                  \
  TREE_TYPE ((gcc_checking_assert (DECL_CONV_FN_P (FN)), DECL_NAME (FN)))

/* Nonzero if NODE, a static data member, was declared in its class as an
   array of unknown bound.  */
#define VAR_HAD_UNKNOWN_BOUND(NODE)                                            \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))                                  \
     ? DECL_LANG_SPECIFIC (NODE)->u.base.unknown_bound_p                       \
     : false)
#define SET_VAR_HAD_UNKNOWN_BOUND(NODE)                                        \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))->u.base.unknown_bound_p = true)

/* True iff decl NODE is for an overloaded operator.  */
#define DECL_OVERLOADED_OPERATOR_P(NODE) IDENTIFIER_ANY_OP_P (DECL_NAME (NODE))

/* Nonzero if NODE is an assignment operator (including += and such).  */
#define DECL_ASSIGNMENT_OPERATOR_P(NODE)                                       \
  IDENTIFIER_ASSIGN_OP_P (DECL_NAME (NODE))

/* NODE is a function_decl for an overloaded operator.  Return its
   compressed (raw) operator code.  Note that this is not a TREE_CODE.  */
#define DECL_OVERLOADED_OPERATOR_CODE_RAW(NODE)                                \
  (LANG_DECL_FN_CHECK (NODE)->ovl_op_code)

/* DECL is an overloaded operator.  Test whether it is for TREE_CODE
   (a literal constant).  */
#define DECL_OVERLOADED_OPERATOR_IS(DECL, CODE)                                \
  (DECL_OVERLOADED_OPERATOR_CODE_RAW (DECL) == OVL_OP_##CODE)

/* For FUNCTION_DECLs: nonzero means that this function is a
   constructor or a destructor with an extra in-charge parameter to
   control whether or not virtual bases are constructed.  */
#define DECL_HAS_IN_CHARGE_PARM_P(NODE)                                        \
  (LANG_DECL_FN_CHECK (NODE)->has_in_charge_parm_p)

/* Nonzero if DECL is a declaration of __builtin_constant_p.  */
#define DECL_IS_BUILTIN_CONSTANT_P(NODE)                                       \
  (TREE_CODE (NODE) == FUNCTION_DECL                                           \
   && DECL_BUILT_IN_CLASS (NODE) == BUILT_IN_NORMAL                            \
   && DECL_FUNCTION_CODE (NODE) == BUILT_IN_CONSTANT_P)

/* Nonzero for _DECL means that this decl appears in (or will appear
   in) as a member in a RECORD_TYPE or UNION_TYPE node.  It is also for
   detecting circularity in case members are multiply defined.  In the
   case of a VAR_DECL, it means that no definition has been seen, even
   if an initializer has been.  */
#define DECL_IN_AGGR_P(NODE) (DECL_LANG_FLAG_3 (NODE))

/* Nonzero for a VAR_DECL means that the variable's initialization (if
   any) has been processed.  (In general, DECL_INITIALIZED_P is
   !DECL_EXTERNAL, but static data members may be initialized even if
   not defined.)  */
#define DECL_INITIALIZED_P(NODE) (TREE_LANG_FLAG_1 (VAR_DECL_CHECK (NODE)))

/* Nonzero for a VAR_DECL iff an explicit initializer was provided
   or a non-trivial constructor is called.  */
#define DECL_NONTRIVIALLY_INITIALIZED_P(NODE)                                  \
  (TREE_LANG_FLAG_6 (VAR_DECL_CHECK (NODE)))

/* Nonzero for a VAR_DECL that was initialized with a
   constant-expression.  */
#define DECL_INITIALIZED_BY_CONSTANT_EXPRESSION_P(NODE)                        \
  (TREE_LANG_FLAG_2 (VAR_DECL_CHECK (NODE)))

/* Nonzero if the DECL was initialized in the class definition itself,
   rather than outside the class.  This is used for both static member
   VAR_DECLS, and FUNCTION_DECLS that are defined in the class.  */
#define DECL_INITIALIZED_IN_CLASS_P(DECL)                                      \
  (DECL_LANG_SPECIFIC (VAR_OR_FUNCTION_DECL_CHECK (DECL))                      \
     ->u.base.initialized_in_class)

/* Nonzero if the DECL is used in the sense of 3.2 [basic.def.odr].
   Only available for decls with DECL_LANG_SPECIFIC.  */
#define DECL_ODR_USED(DECL)                                                    \
  (DECL_LANG_SPECIFIC (VAR_OR_FUNCTION_DECL_CHECK (DECL))->u.base.odr_used)

/* Nonzero for FUNCTION_DECL means that this is a friend that is
   either not pushed into a namespace/looked up in a class (because it
   is a dependent type, in an uninstantiated template), or it has
   /only/ been subject to hidden friend injection from one or more
   befriending classes.  Once another decl matches, the flag is
   cleared.  There are requirements on its default parms.  */
#define DECL_UNIQUE_FRIEND_P(NODE)                                             \
  (DECL_LANG_SPECIFIC (FUNCTION_DECL_CHECK (NODE))->u.base.friend_or_tls)

/* True of a TEMPLATE_DECL that is a template class friend.  Such
   decls are not pushed until instantiated (as they may depend on
   parameters of the befriending class).  DECL_CHAIN is the
   befriending class.  */
#define DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P(NODE)                            \
  (DECL_LANG_FLAG_4 (TEMPLATE_DECL_CHECK (NODE)))

/* Nonzero if the thread-local variable was declared with __thread as
   opposed to thread_local.  */
#define DECL_GNU_TLS_P(NODE)                                                   \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))                                  \
   && DECL_LANG_SPECIFIC (NODE)->u.base.friend_or_tls)
#define SET_DECL_GNU_TLS_P(NODE)                                               \
  (retrofit_lang_decl (VAR_DECL_CHECK (NODE)),                                 \
   DECL_LANG_SPECIFIC (NODE)->u.base.friend_or_tls = true)

/* A TREE_LIST of the types which have befriended this FUNCTION_DECL.  */
#define DECL_BEFRIENDING_CLASSES(NODE)                                         \
  (LANG_DECL_FN_CHECK (NODE)->befriending_classes)

/* Nonzero for FUNCTION_DECL means that this decl is a static
   member function.  */
#define DECL_STATIC_FUNCTION_P(NODE)                                           \
  (LANG_DECL_FN_CHECK (NODE)->static_function)

/* Nonzero for FUNCTION_DECL means that this decl is a non-static
   member function.  */
#define DECL_NONSTATIC_MEMBER_FUNCTION_P(NODE)                                 \
  (TREE_CODE (TREE_TYPE (NODE)) == METHOD_TYPE)

/* Nonzero for FUNCTION_DECL means that this decl is a member function
   (static or non-static).  */
#define DECL_FUNCTION_MEMBER_P(NODE)                                           \
  (DECL_NONSTATIC_MEMBER_FUNCTION_P (NODE) || DECL_STATIC_FUNCTION_P (NODE))

/* Nonzero for FUNCTION_DECL means that this member function
   has `this' as const X *const.  */
#define DECL_CONST_MEMFUNC_P(NODE)                                             \
  (DECL_NONSTATIC_MEMBER_FUNCTION_P (NODE)                                     \
   && CP_TYPE_CONST_P (                                                        \
     TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (TREE_TYPE (NODE))))))

/* Nonzero for FUNCTION_DECL means that this member function
   has `this' as volatile X *const.  */
#define DECL_VOLATILE_MEMFUNC_P(NODE)                                          \
  (DECL_NONSTATIC_MEMBER_FUNCTION_P (NODE)                                     \
   && CP_TYPE_VOLATILE_P (                                                     \
     TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (TREE_TYPE (NODE))))))

/* Nonzero for a DECL means that this member is a non-static member.  */
#define DECL_NONSTATIC_MEMBER_P(NODE)                                          \
  (DECL_NONSTATIC_MEMBER_FUNCTION_P (NODE) || TREE_CODE (NODE) == FIELD_DECL)

/* Nonzero for a FIELD_DECL means that this member object type
   is mutable.  */
#define DECL_MUTABLE_P(NODE) (DECL_LANG_FLAG_0 (FIELD_DECL_CHECK (NODE)))

/* Nonzero for _DECL means that this constructor or conversion function is
   non-converting.  */
#define DECL_NONCONVERTING_P(NODE) (LANG_DECL_FN_CHECK (NODE)->nonconverting)

/* Nonzero for FUNCTION_DECL means that this member function is a pure
   virtual function.  */
#define DECL_PURE_VIRTUAL_P(NODE) (LANG_DECL_FN_CHECK (NODE)->pure_virtual)

/* Nonzero for FUNCTION_DECL means that this member function (either
   a constructor or a conversion function) has an explicit specifier
   with a value-dependent expression.  */
#define DECL_HAS_DEPENDENT_EXPLICIT_SPEC_P(NODE)                               \
  (LANG_DECL_FN_CHECK (NODE)->has_dependent_explicit_spec_p)

/* Nonzero for a defaulted FUNCTION_DECL for which we haven't decided yet if
   it's deleted; we will decide in synthesize_method.  */
#define DECL_MAYBE_DELETED(NODE) (LANG_DECL_FN_CHECK (NODE)->maybe_deleted)

/* True (in a FUNCTION_DECL) if NODE is a virtual function that is an
   invalid overrider for a function from a base class.  Once we have
   complained about an invalid overrider we avoid complaining about it
   again.  */
#define DECL_INVALID_OVERRIDER_P(NODE) (DECL_LANG_FLAG_4 (NODE))

/* True (in a FUNCTION_DECL) if NODE is a function declared with
   an override virt-specifier */
#define DECL_OVERRIDE_P(NODE) (TREE_LANG_FLAG_0 (NODE))

/* The thunks associated with NODE, a FUNCTION_DECL.  */
#define DECL_THUNKS(NODE)                                                      \
  (DECL_VIRTUAL_P (NODE) ? LANG_DECL_FN_CHECK (NODE)->context : NULL_TREE)

/* Set DECL_THUNKS.  */
#define SET_DECL_THUNKS(NODE, THUNKS)                                          \
  (LANG_DECL_FN_CHECK (NODE)->context = (THUNKS))

/* If NODE, a FUNCTION_DECL, is a C++11 inheriting constructor, then this
   is the constructor it inherits from.  */
#define DECL_INHERITED_CTOR(NODE)                                              \
  (DECL_DECLARES_FUNCTION_P (NODE) && DECL_CONSTRUCTOR_P (NODE)                \
     ? LANG_DECL_FN_CHECK (NODE)->context                                      \
     : NULL_TREE)

/* And this is the base that constructor comes from.  */
#define DECL_INHERITED_CTOR_BASE(NODE)                                         \
  (DECL_INHERITED_CTOR (NODE)                                                  \
     ? DECL_CONTEXT (flag_new_inheriting_ctors ? strip_inheriting_ctors (NODE) \
					       : DECL_INHERITED_CTOR (NODE))   \
     : NULL_TREE)

/* Set the inherited base.  */
#define SET_DECL_INHERITED_CTOR(NODE, INH)                                     \
  (LANG_DECL_FN_CHECK (NODE)->context = (INH))

/* Nonzero if NODE is a thunk, rather than an ordinary function.  */
#define DECL_THUNK_P(NODE)                                                     \
  (TREE_CODE (NODE) == FUNCTION_DECL && DECL_LANG_SPECIFIC (NODE)              \
   && LANG_DECL_FN_CHECK (NODE)->thunk_p)

/* Set DECL_THUNK_P for node.  */
#define SET_DECL_THUNK_P(NODE, THIS_ADJUSTING)                                 \
  (LANG_DECL_FN_CHECK (NODE)->thunk_p = 1,                                     \
   LANG_DECL_FN_CHECK (NODE)->this_thunk_p = (THIS_ADJUSTING))

/* Nonzero if NODE is a this pointer adjusting thunk.  */
#define DECL_THIS_THUNK_P(NODE)                                                \
  (DECL_THUNK_P (NODE) && LANG_DECL_FN_CHECK (NODE)->this_thunk_p)

/* Nonzero if NODE is a result pointer adjusting thunk.  */
#define DECL_RESULT_THUNK_P(NODE)                                              \
  (DECL_THUNK_P (NODE) && !LANG_DECL_FN_CHECK (NODE)->this_thunk_p)

/* Nonzero if NODE is a FUNCTION_DECL, but not a thunk.  */
#define DECL_NON_THUNK_FUNCTION_P(NODE)                                        \
  (TREE_CODE (NODE) == FUNCTION_DECL && !DECL_THUNK_P (NODE))

/* Nonzero if NODE is `extern "C"'.  */
#define DECL_EXTERN_C_P(NODE) (DECL_LANGUAGE (NODE) == lang_c)

/* Nonzero if NODE is an `extern "C"' function.  */
#define DECL_EXTERN_C_FUNCTION_P(NODE)                                         \
  (DECL_NON_THUNK_FUNCTION_P (NODE) && DECL_EXTERN_C_P (NODE))

/* Non-zero if this variable is declared `constinit' specifier.  */
#define DECL_DECLARED_CONSTINIT_P(NODE)                                        \
  (DECL_LANG_FLAG_7 (VAR_DECL_CHECK (NODE)))

/* True if DECL is declared 'constexpr'.  */
#define DECL_DECLARED_CONSTEXPR_P(DECL)                                        \
  DECL_LANG_FLAG_8 (VAR_OR_FUNCTION_DECL_CHECK (STRIP_TEMPLATE (DECL)))

/* True if FNDECL is an immediate function.  */
#define DECL_IMMEDIATE_FUNCTION_P(NODE)                                        \
  (DECL_LANG_SPECIFIC (FUNCTION_DECL_CHECK (STRIP_TEMPLATE (NODE)))            \
     ? LANG_DECL_FN_CHECK (NODE)->immediate_fn_p                               \
     : false)
#define SET_DECL_IMMEDIATE_FUNCTION_P(NODE)                                    \
  (retrofit_lang_decl (FUNCTION_DECL_CHECK (NODE)),                            \
   LANG_DECL_FN_CHECK (NODE)->immediate_fn_p = true)

// True if NODE was declared as 'concept'.  The flag implies that the
// declaration is constexpr, that the declaration cannot be specialized or
// refined, and that the result type must be convertible to bool.
#define DECL_DECLARED_CONCEPT_P(NODE)                                          \
  (DECL_LANG_SPECIFIC (NODE)->u.base.concept_p)

/* Nonzero if this DECL is the __PRETTY_FUNCTION__ variable in a
   template function.  */
#define DECL_PRETTY_FUNCTION_P(NODE)                                           \
  (DECL_NAME (NODE) && id_equal (DECL_NAME (NODE), "__PRETTY_FUNCTION__"))

/* For a DECL, true if it is __func__ or similar.  */
#define DECL_FNAME_P(NODE)                                                     \
  (VAR_P (NODE) && DECL_NAME (NODE) && DECL_ARTIFICIAL (NODE)                  \
   && DECL_HAS_VALUE_EXPR_P (NODE)                                             \
   && (id_equal (DECL_NAME (NODE), "__PRETTY_FUNCTION__")                      \
       || id_equal (DECL_NAME (NODE), "__FUNCTION__")                          \
       || id_equal (DECL_NAME (NODE), "__func__")))

/* Nonzero if the variable was declared to be thread-local.
   We need a special C++ version of this test because the middle-end
   DECL_THREAD_LOCAL_P uses the symtab, so we can't use it for
   templates.  */
#define CP_DECL_THREAD_LOCAL_P(NODE) (TREE_LANG_FLAG_0 (VAR_DECL_CHECK (NODE)))

/* The _TYPE context in which this _DECL appears.  This field holds the
   class where a virtual function instance is actually defined.  */
#define DECL_CLASS_CONTEXT(NODE)                                               \
  (DECL_CLASS_SCOPE_P (NODE) ? DECL_CONTEXT (NODE) : NULL_TREE)

/* For a non-member friend function, the class (if any) in which this
   friend was defined.  For example, given:

     struct S { friend void f () { ... } };

   the DECL_FRIEND_CONTEXT for `f' will be `S'.  */
#define DECL_FRIEND_CONTEXT(NODE)                                              \
  ((DECL_DECLARES_FUNCTION_P (NODE) && !DECL_VIRTUAL_P (NODE)                  \
    && !DECL_CONSTRUCTOR_P (NODE))                                             \
     ? LANG_DECL_FN_CHECK (NODE)->context                                      \
     : NULL_TREE)

/* Set the DECL_FRIEND_CONTEXT for NODE to CONTEXT.  */
#define SET_DECL_FRIEND_CONTEXT(NODE, CONTEXT)                                 \
  (LANG_DECL_FN_CHECK (NODE)->context = (CONTEXT))

#define CP_DECL_CONTEXT(NODE)                                                  \
  (!DECL_FILE_SCOPE_P (NODE) ? DECL_CONTEXT (NODE) : global_namespace)
#define CP_TYPE_CONTEXT(NODE)                                                  \
  (!TYPE_FILE_SCOPE_P (NODE) ? TYPE_CONTEXT (NODE) : global_namespace)
#define FROB_CONTEXT(NODE)                                                     \
  ((NODE) == global_namespace ? DECL_CONTEXT (NODE) : (NODE))

/* 1 iff NODE has namespace scope, including the global namespace.  */
#define DECL_NAMESPACE_SCOPE_P(NODE)                                           \
  (!DECL_TEMPLATE_PARM_P (NODE)                                                \
   && TREE_CODE (CP_DECL_CONTEXT (NODE)) == NAMESPACE_DECL)

#define TYPE_NAMESPACE_SCOPE_P(NODE)                                           \
  (TREE_CODE (CP_TYPE_CONTEXT (NODE)) == NAMESPACE_DECL)

#define NAMESPACE_SCOPE_P(NODE)                                                \
  ((DECL_P (NODE) && DECL_NAMESPACE_SCOPE_P (NODE))                            \
   || (TYPE_P (NODE) && TYPE_NAMESPACE_SCOPE_P (NODE)))

/* 1 iff NODE is a class member.  */
#define DECL_CLASS_SCOPE_P(NODE)                                               \
  (DECL_CONTEXT (NODE) && TYPE_P (DECL_CONTEXT (NODE)))

#define TYPE_CLASS_SCOPE_P(NODE)                                               \
  (TYPE_CONTEXT (NODE) && TYPE_P (TYPE_CONTEXT (NODE)))

/* 1 iff NODE is function-local.  */
#define DECL_FUNCTION_SCOPE_P(NODE)                                            \
  (DECL_CONTEXT (NODE) && TREE_CODE (DECL_CONTEXT (NODE)) == FUNCTION_DECL)

#define TYPE_FUNCTION_SCOPE_P(NODE)                                            \
  (TYPE_CONTEXT (NODE) && TREE_CODE (TYPE_CONTEXT (NODE)) == FUNCTION_DECL)

/* 1 iff VAR_DECL node NODE is a type-info decl.  This flag is set for
   both the primary typeinfo object and the associated NTBS name.  */
#define DECL_TINFO_P(NODE)                                                     \
  TREE_LANG_FLAG_4 (TREE_CHECK2 (NODE, VAR_DECL, TYPE_DECL))

/* 1 iff VAR_DECL node NODE is virtual table or VTT.  We forward to
   DECL_VIRTUAL_P from the common code, as that has the semantics we
   need.  But we want a more descriptive name.  */
#define DECL_VTABLE_OR_VTT_P(NODE) DECL_VIRTUAL_P (VAR_DECL_CHECK (NODE))

/* 1 iff FUNCTION_TYPE or METHOD_TYPE has a ref-qualifier (either & or &&). */
#define FUNCTION_REF_QUALIFIED(NODE)                                           \
  TREE_LANG_FLAG_4 (FUNC_OR_METHOD_CHECK (NODE))

/* 1 iff FUNCTION_TYPE or METHOD_TYPE has &&-ref-qualifier.  */
#define FUNCTION_RVALUE_QUALIFIED(NODE)                                        \
  TREE_LANG_FLAG_5 (FUNC_OR_METHOD_CHECK (NODE))

/* 1 iff NODE is function-local, but for types.  */
#define LOCAL_CLASS_P(NODE)                                                    \
  (decl_function_context (TYPE_MAIN_DECL (NODE)) != NULL_TREE)

/* The nesting depth of namespace, class or function.  Makes is_ancestor much
   simpler.  Only 8 bits available.  */
#define SCOPE_DEPTH(NODE)                                                      \
  (NAMESPACE_DECL_CHECK (NODE)->base.u.bits.address_space)

/* Whether the namepace is an inline namespace.  */
#define DECL_NAMESPACE_INLINE_P(NODE)                                          \
  TREE_LANG_FLAG_0 (NAMESPACE_DECL_CHECK (NODE))

/* In a NAMESPACE_DECL, a vector of inline namespaces.  */
#define DECL_NAMESPACE_INLINEES(NODE) (LANG_DECL_NS_CHECK (NODE)->inlinees)

/* Pointer to hash_map from IDENTIFIERS to DECLS  */
#define DECL_NAMESPACE_BINDINGS(NODE) (LANG_DECL_NS_CHECK (NODE)->bindings)

/* In a NAMESPACE_DECL, points to the original namespace if this is
   a namespace alias.  */
#define DECL_NAMESPACE_ALIAS(NODE)                                             \
  DECL_ABSTRACT_ORIGIN (NAMESPACE_DECL_CHECK (NODE))
#define ORIGINAL_NAMESPACE(NODE)                                               \
  (DECL_NAMESPACE_ALIAS (NODE) ? DECL_NAMESPACE_ALIAS (NODE) : (NODE))

/* Nonzero if NODE is the std namespace.  */
#define DECL_NAMESPACE_STD_P(NODE) ((NODE) == std_node)

/* In a TREE_LIST in an attribute list, indicates that the attribute
   must be applied at instantiation time.  */
#define ATTR_IS_DEPENDENT(NODE) TREE_LANG_FLAG_0 (TREE_LIST_CHECK (NODE))

/* In a TREE_LIST in the argument of attribute abi_tag, indicates that the tag
   was inherited from a template parameter, not explicitly indicated.  */
#define ABI_TAG_IMPLICIT(NODE) TREE_LANG_FLAG_0 (TREE_LIST_CHECK (NODE))

/* In a TREE_LIST for a parameter-declaration-list, indicates that all the
   parameters in the list have declarators enclosed in ().  */
#define PARENTHESIZED_LIST_P(NODE) TREE_LANG_FLAG_0 (TREE_LIST_CHECK (NODE))

/* Non zero if this is a using decl for a dependent scope. */
#define DECL_DEPENDENT_P(NODE) DECL_LANG_FLAG_0 (USING_DECL_CHECK (NODE))

/* The scope named in a using decl.  */
#define USING_DECL_SCOPE(NODE) DECL_RESULT_FLD (USING_DECL_CHECK (NODE))

/* The decls named by a using decl.  */
#define USING_DECL_DECLS(NODE) DECL_INITIAL (USING_DECL_CHECK (NODE))

/* Non zero if the using decl refers to a dependent type.  */
#define USING_DECL_TYPENAME_P(NODE) DECL_LANG_FLAG_1 (USING_DECL_CHECK (NODE))

/* True if member using decl NODE refers to a non-inherited NODE.  */
#define USING_DECL_UNRELATED_P(NODE) DECL_LANG_FLAG_2 (USING_DECL_CHECK (NODE))

/* True iff the CONST_DECL is a class-scope clone from C++20 using enum,
   created by handle_using_decl.  */
#define CONST_DECL_USING_P(NODE)                                               \
  (TREE_CODE (NODE) == CONST_DECL && TREE_TYPE (NODE)                          \
   && TREE_CODE (TREE_TYPE (NODE)) == ENUMERAL_TYPE                            \
   && DECL_CONTEXT (NODE) != TREE_TYPE (NODE))

/* In a FUNCTION_DECL, this is nonzero if this function was defined in
   the class definition.  We have saved away the text of the function,
   but have not yet processed it.  */
#define DECL_PENDING_INLINE_P(NODE)                                            \
  (LANG_DECL_FN_CHECK (NODE)->pending_inline_p)

/* If DECL_PENDING_INLINE_P holds, this is the saved text of the
   function.  */
#define DECL_PENDING_INLINE_INFO(NODE)                                         \
  (LANG_DECL_FN_CHECK (NODE)->u.pending_inline_info)

/* Nonzero for TYPE_DECL means that it was written 'using name = type'.  */
#define TYPE_DECL_ALIAS_P(NODE) DECL_LANG_FLAG_6 (TYPE_DECL_CHECK (NODE))

/* Nonzero for TEMPLATE_DECL means that it is a 'complex' alias template.  */
#define TEMPLATE_DECL_COMPLEX_ALIAS_P(NODE)                                    \
  DECL_LANG_FLAG_2 (TEMPLATE_DECL_CHECK (NODE))

/* Nonzero for a type which is an alias for another type; i.e, a type
   which declaration was written 'using name-of-type =
   another-type'.  */
#define TYPE_ALIAS_P(NODE)                                                     \
  (TYPE_P (NODE) && TYPE_NAME (NODE)                                           \
   && TREE_CODE (TYPE_NAME (NODE)) == TYPE_DECL                                \
   && TYPE_DECL_ALIAS_P (TYPE_NAME (NODE)))

/* If non-NULL for a VAR_DECL, FUNCTION_DECL, TYPE_DECL, TEMPLATE_DECL,
   or CONCEPT_DECL, the entity is either a template specialization (if
   DECL_USE_TEMPLATE is nonzero) or the abstract instance of the
   template itself.

   In either case, DECL_TEMPLATE_INFO is a TEMPLATE_INFO, whose
   TI_TEMPLATE is the TEMPLATE_DECL of which this entity is a
   specialization or abstract instance.  The TI_ARGS is the
   template arguments used to specialize the template.

   Consider:

      template <typename T> struct S { friend void f(T) {} };

   In this case, S<int>::f is, from the point of view of the compiler,
   an instantiation of a template -- but, from the point of view of
   the language, each instantiation of S results in a wholly unrelated
   global function f.  In this case, DECL_TEMPLATE_INFO for S<int>::f
   will be non-NULL, but DECL_USE_TEMPLATE will be zero.

   In a friend declaration, TI_TEMPLATE can be an overload set, or
   identifier.  */
#define DECL_TEMPLATE_INFO(NODE)                                               \
  (DECL_LANG_SPECIFIC (TEMPLATE_INFO_DECL_CHECK (NODE))->u.min.template_info)

/* For a lambda capture proxy, its captured variable.  */
#define DECL_CAPTURED_VARIABLE(NODE) (LANG_DECL_MIN_CHECK (NODE)->access)

/* For a VAR_DECL, indicates that the variable is actually a
   non-static data member of anonymous union that has been promoted to
   variable status.  */
#define DECL_ANON_UNION_VAR_P(NODE) (DECL_LANG_FLAG_4 (VAR_DECL_CHECK (NODE)))

/* Template information for a RECORD_TYPE or UNION_TYPE.  */
#define CLASSTYPE_TEMPLATE_INFO(NODE)                                          \
  (TYPE_LANG_SLOT_1 (RECORD_OR_UNION_CHECK (NODE)))

/* Template information for a template template parameter.  */
#define TEMPLATE_TEMPLATE_PARM_TEMPLATE_INFO(NODE)                             \
  (TYPE_LANG_SLOT_1 (BOUND_TEMPLATE_TEMPLATE_PARM_TYPE_CHECK (NODE)))

/* Template information for an ENUMERAL_, RECORD_, UNION_TYPE, or
   BOUND_TEMPLATE_TEMPLATE_PARM type.  This ignores any alias
   templateness of NODE.  It'd be nice if this could unconditionally
   access the slot, rather than return NULL if given a
   non-templatable type.  */
#define TYPE_TEMPLATE_INFO(NODE)                                               \
  (TREE_CODE (NODE) == ENUMERAL_TYPE                                           \
       || TREE_CODE (NODE) == BOUND_TEMPLATE_TEMPLATE_PARM                     \
       || RECORD_OR_UNION_TYPE_P (NODE)                                        \
     ? TYPE_LANG_SLOT_1 (NODE)                                                 \
     : NULL_TREE)

/* Template information (if any) for an alias type.  */
#define TYPE_ALIAS_TEMPLATE_INFO(NODE)                                         \
  (DECL_LANG_SPECIFIC (TYPE_NAME (NODE))                                       \
     ? DECL_TEMPLATE_INFO (TYPE_NAME (NODE))                                   \
     : NULL_TREE)

/* If NODE is a type alias, this accessor returns the template info
   for the alias template (if any).  Otherwise behave as
   TYPE_TEMPLATE_INFO.  */
#define TYPE_TEMPLATE_INFO_MAYBE_ALIAS(NODE)                                   \
  (typedef_variant_p (NODE) ? TYPE_ALIAS_TEMPLATE_INFO (NODE)                  \
			    : TYPE_TEMPLATE_INFO (NODE))

/* Set the template information for a non-alias n ENUMERAL_, RECORD_,
   or UNION_TYPE to VAL.  ALIAS's are dealt with separately.  */
#define SET_TYPE_TEMPLATE_INFO(NODE, VAL)                                      \
  (TREE_CODE (NODE) == ENUMERAL_TYPE                                           \
       || (CLASS_TYPE_P (NODE) && !TYPE_ALIAS_P (NODE))                        \
     ? (TYPE_LANG_SLOT_1 (NODE) = (VAL))                                       \
     : (DECL_TEMPLATE_INFO (TYPE_NAME (NODE)) = (VAL)))

#define TI_TEMPLATE(NODE)                                                      \
  ((struct tree_template_info *) TEMPLATE_INFO_CHECK (NODE))->tmpl
#define TI_ARGS(NODE)                                                          \
  ((struct tree_template_info *) TEMPLATE_INFO_CHECK (NODE))->args
#define TI_PENDING_TEMPLATE_FLAG(NODE)                                         \
  TREE_LANG_FLAG_1 (TEMPLATE_INFO_CHECK (NODE))
/* For a given TREE_VEC containing a template argument list,
   this property contains the number of arguments that are not
   defaulted.  */
#define NON_DEFAULT_TEMPLATE_ARGS_COUNT(NODE) TREE_CHAIN (TREE_VEC_CHECK (NODE))

/* Below are the setter and getter of the NON_DEFAULT_TEMPLATE_ARGS_COUNT
   property.  */
#define SET_NON_DEFAULT_TEMPLATE_ARGS_COUNT(NODE, INT_VALUE)                   \
  NON_DEFAULT_TEMPLATE_ARGS_COUNT (NODE) = build_int_cst (NULL_TREE, INT_VALUE)
#if CHECKING_P
#define GET_NON_DEFAULT_TEMPLATE_ARGS_COUNT(NODE)                              \
  int_cst_value (NON_DEFAULT_TEMPLATE_ARGS_COUNT (NODE))
#else
#define GET_NON_DEFAULT_TEMPLATE_ARGS_COUNT(NODE)                              \
  NON_DEFAULT_TEMPLATE_ARGS_COUNT (NODE)                                       \
  ? int_cst_value (NON_DEFAULT_TEMPLATE_ARGS_COUNT (NODE))                     \
  : TREE_VEC_LENGTH (INNERMOST_TEMPLATE_ARGS (NODE))
#endif

/* The list of access checks that were deferred during parsing
   which need to be performed at template instantiation time.

   FIXME this should be associated with the TEMPLATE_DECL, not the
   TEMPLATE_INFO.  */
#define TI_DEFERRED_ACCESS_CHECKS(NODE)                                        \
  ((struct tree_template_info *) TEMPLATE_INFO_CHECK (NODE))                   \
    ->deferred_access_checks

/* We use TREE_VECs to hold template arguments.  If there is only one
   level of template arguments, then the TREE_VEC contains the
   arguments directly.  If there is more than one level of template
   arguments, then each entry in the TREE_VEC is itself a TREE_VEC,
   containing the template arguments for a single level.  The first
   entry in the outer TREE_VEC is the outermost level of template
   parameters; the last is the innermost.

   It is incorrect to ever form a template argument vector containing
   only one level of arguments, but which is a TREE_VEC containing as
   its only entry the TREE_VEC for that level.

   For each TREE_VEC containing the template arguments for a single
   level, it's possible to get or set the number of non defaulted
   template arguments by using the accessor macros
   GET_NON_DEFAULT_TEMPLATE_ARGS_COUNT or
   SET_NON_DEFAULT_TEMPLATE_ARGS_COUNT.  */

/* Nonzero if the template arguments is actually a vector of vectors,
   rather than just a vector.  */
#define TMPL_ARGS_HAVE_MULTIPLE_LEVELS(NODE)                                   \
  (NODE && TREE_VEC_LENGTH (NODE) && TREE_VEC_ELT (NODE, 0)                    \
   && TREE_CODE (TREE_VEC_ELT (NODE, 0)) == TREE_VEC)

/* The depth of a template argument vector.  When called directly by
   the parser, we use a TREE_LIST rather than a TREE_VEC to represent
   template arguments.  In fact, we may even see NULL_TREE if there
   are no template arguments.  In both of those cases, there is only
   one level of template arguments.  */
#define TMPL_ARGS_DEPTH(NODE)                                                  \
  (TMPL_ARGS_HAVE_MULTIPLE_LEVELS (NODE) ? TREE_VEC_LENGTH (NODE) : 1)

/* The LEVELth level of the template ARGS.  The outermost level of
   args is level 1, not level 0.  */
#define TMPL_ARGS_LEVEL(ARGS, LEVEL)                                           \
  (TMPL_ARGS_HAVE_MULTIPLE_LEVELS (ARGS) ? TREE_VEC_ELT (ARGS, (LEVEL) -1)     \
					 : (ARGS))

/* Set the LEVELth level of the template ARGS to VAL.  This macro does
   not work with single-level argument vectors.  */
#define SET_TMPL_ARGS_LEVEL(ARGS, LEVEL, VAL)                                  \
  (TREE_VEC_ELT (ARGS, (LEVEL) -1) = (VAL))

/* Accesses the IDXth parameter in the LEVELth level of the ARGS.  */
#define TMPL_ARG(ARGS, LEVEL, IDX)                                             \
  (TREE_VEC_ELT (TMPL_ARGS_LEVEL (ARGS, LEVEL), IDX))

/* Given a single level of template arguments in NODE, return the
   number of arguments.  */
#define NUM_TMPL_ARGS(NODE) (TREE_VEC_LENGTH (NODE))

/* Returns the innermost level of template arguments in ARGS.  */
#define INNERMOST_TEMPLATE_ARGS(NODE) (get_innermost_template_args ((NODE), 1))

/* The number of levels of template parameters given by NODE.  */
#define TMPL_PARMS_DEPTH(NODE)                                                 \
  ((HOST_WIDE_INT) TREE_INT_CST_LOW (TREE_PURPOSE (NODE)))

/* The TEMPLATE_DECL instantiated or specialized by NODE.  This
   TEMPLATE_DECL will be the immediate parent, not the most general
   template.  For example, in:

      template <class T> struct S { template <class U> void f(U); }

   the FUNCTION_DECL for S<int>::f<double> will have, as its
   DECL_TI_TEMPLATE, `template <class U> S<int>::f<U>'.

   As a special case, for a member friend template of a template
   class, this value will not be a TEMPLATE_DECL, but rather an
   IDENTIFIER_NODE or OVERLOAD indicating the name of the template and
   any explicit template arguments provided.  For example, in:

     template <class T> struct S { friend void f<int>(int, double); }

   the DECL_TI_TEMPLATE will be an IDENTIFIER_NODE for `f' and the
   DECL_TI_ARGS will be {int}.

   For a FIELD_DECL with a non-static data member initializer, this value
   is the FIELD_DECL it was instantiated from.  */
#define DECL_TI_TEMPLATE(NODE) TI_TEMPLATE (DECL_TEMPLATE_INFO (NODE))

/* The template arguments used to obtain this decl from the most
   general form of DECL_TI_TEMPLATE.  For the example given for
   DECL_TI_TEMPLATE, the DECL_TI_ARGS will be {int, double}.  These
   are always the full set of arguments required to instantiate this
   declaration from the most general template specialized here.  */
#define DECL_TI_ARGS(NODE) TI_ARGS (DECL_TEMPLATE_INFO (NODE))

/* The TEMPLATE_DECL associated with NODE, a class type.  Even if NODE
   will be generated from a partial specialization, the TEMPLATE_DECL
   referred to here will be the original template.  For example,
   given:

      template <typename T> struct S {};
      template <typename T> struct S<T*> {};

   the CLASSTYPE_TI_TEMPLATE for S<int*> will be S, not the S<T*>.

   For a member class template, CLASSTYPE_TI_TEMPLATE always refers to the
   partial instantiation rather than the primary template.  CLASSTYPE_TI_ARGS
   are for the primary template if the partial instantiation isn't
   specialized, or for the explicit specialization if it is, e.g.

      template <class T> class C { template <class U> class D; }
      template <> template <class U> class C<int>::D;  */
#define CLASSTYPE_TI_TEMPLATE(NODE) TI_TEMPLATE (CLASSTYPE_TEMPLATE_INFO (NODE))
#define CLASSTYPE_TI_ARGS(NODE) TI_ARGS (CLASSTYPE_TEMPLATE_INFO (NODE))

/* For a template instantiation TYPE, returns the TYPE corresponding
   to the primary template.  Otherwise returns TYPE itself.  */
#define CLASSTYPE_PRIMARY_TEMPLATE_TYPE(TYPE)                                  \
  ((CLASSTYPE_USE_TEMPLATE ((TYPE))                                            \
    && !CLASSTYPE_TEMPLATE_SPECIALIZATION ((TYPE)))                            \
     ? TREE_TYPE (DECL_TEMPLATE_RESULT (                                       \
       DECL_PRIMARY_TEMPLATE (CLASSTYPE_TI_TEMPLATE ((TYPE)))))                \
     : (TYPE))

/* Like CLASS_TI_TEMPLATE, but also works for ENUMERAL_TYPEs.  */
#define TYPE_TI_TEMPLATE(NODE) (TI_TEMPLATE (TYPE_TEMPLATE_INFO (NODE)))

/* Like DECL_TI_ARGS, but for an ENUMERAL_, RECORD_, or UNION_TYPE.  */
#define TYPE_TI_ARGS(NODE) (TI_ARGS (TYPE_TEMPLATE_INFO (NODE)))

#define INNERMOST_TEMPLATE_PARMS(NODE) TREE_VALUE (NODE)

/* Nonzero if NODE (a TEMPLATE_DECL) is a member template, in the
   sense of [temp.mem].  */
#define DECL_MEMBER_TEMPLATE_P(NODE)                                           \
  (DECL_LANG_FLAG_1 (TEMPLATE_DECL_CHECK (NODE)))

/* Nonzero if the NODE corresponds to the template parameters for a
   member template, whose inline definition is being processed after
   the class definition is complete.  */
#define TEMPLATE_PARMS_FOR_INLINE(NODE) TREE_LANG_FLAG_1 (NODE)

/* Determine if a declaration (PARM_DECL or FIELD_DECL) is a pack.  */
#define DECL_PACK_P(NODE) (DECL_P (NODE) && PACK_EXPANSION_P (TREE_TYPE (NODE)))

/* Determines if NODE is an expansion of one or more parameter packs,
   e.g., a TYPE_PACK_EXPANSION or EXPR_PACK_EXPANSION.  */
#define PACK_EXPANSION_P(NODE)                                                 \
  (TREE_CODE (NODE) == TYPE_PACK_EXPANSION                                     \
   || TREE_CODE (NODE) == EXPR_PACK_EXPANSION)

/* Extracts the type or expression pattern from a TYPE_PACK_EXPANSION or
   EXPR_PACK_EXPANSION.  */
#define PACK_EXPANSION_PATTERN(NODE)                                           \
  (TREE_CODE (NODE) == TYPE_PACK_EXPANSION ? TREE_TYPE (NODE)                  \
					   : TREE_OPERAND (NODE, 0))

/* Sets the type or expression pattern for a TYPE_PACK_EXPANSION or
   EXPR_PACK_EXPANSION.  */
#define SET_PACK_EXPANSION_PATTERN(NODE, VALUE)                                \
  if (TREE_CODE (NODE) == TYPE_PACK_EXPANSION)                                 \
    TREE_TYPE (NODE) = VALUE;                                                  \
  else                                                                         \
    TREE_OPERAND (NODE, 0) = VALUE

/* The list of parameter packs used in the PACK_EXPANSION_* node. The
   TREE_VALUE of each TREE_LIST contains the parameter packs.  */
#define PACK_EXPANSION_PARAMETER_PACKS(NODE)                                   \
  *(TREE_CODE (NODE) == EXPR_PACK_EXPANSION                                    \
      ? &TREE_OPERAND (NODE, 1)                                                \
      : &TYPE_MIN_VALUE_RAW (TYPE_PACK_EXPANSION_CHECK (NODE)))

/* Any additional template args to be applied when substituting into
   the pattern, set by tsubst_pack_expansion for partial instantiations.
   If this is a TREE_LIST, the TREE_VALUE of the first element is the
   usual template argument TREE_VEC, and the TREE_PURPOSE of later elements
   are enclosing functions that provided function parameter packs we'll need
   to map appropriately.  */
#define PACK_EXPANSION_EXTRA_ARGS(NODE)                                        \
  *(TREE_CODE (NODE) == TYPE_PACK_EXPANSION ? &TYPE_MAX_VALUE_RAW (NODE)       \
					    : &TREE_OPERAND ((NODE), 2))

/* True iff this pack expansion is within a function context.  */
#define PACK_EXPANSION_LOCAL_P(NODE) TREE_LANG_FLAG_0 (NODE)

/* True iff this pack expansion is for sizeof....  */
#define PACK_EXPANSION_SIZEOF_P(NODE) TREE_LANG_FLAG_1 (NODE)

/* True iff this pack expansion is for auto... in lambda init-capture.  */
#define PACK_EXPANSION_AUTO_P(NODE) TREE_LANG_FLAG_2 (NODE)

/* True if we must use PACK_EXPANSION_EXTRA_ARGS and avoid partial
   instantiation of this pack expansion.  */
#define PACK_EXPANSION_FORCE_EXTRA_ARGS_P(NODE) TREE_LANG_FLAG_3 (NODE)

/* True iff the wildcard can match a template parameter pack.  */
#define WILDCARD_PACK_P(NODE) TREE_LANG_FLAG_0 (NODE)

/* Determine if this is an argument pack.  */
#define ARGUMENT_PACK_P(NODE)                                                  \
  (TREE_CODE (NODE) == TYPE_ARGUMENT_PACK                                      \
   || TREE_CODE (NODE) == NONTYPE_ARGUMENT_PACK)

/* The arguments stored in an argument pack. Arguments are stored in a
   TREE_VEC, which may have length zero.  */
#define ARGUMENT_PACK_ARGS(NODE)                                               \
  (TREE_CODE (NODE) == TYPE_ARGUMENT_PACK ? TREE_TYPE (NODE)                   \
					  : TREE_OPERAND (NODE, 0))

/* Set the arguments stored in an argument pack. VALUE must be a
   TREE_VEC.  */
#define SET_ARGUMENT_PACK_ARGS(NODE, VALUE)                                    \
  if (TREE_CODE (NODE) == TYPE_ARGUMENT_PACK)                                  \
    TREE_TYPE (NODE) = VALUE;                                                  \
  else                                                                         \
    TREE_OPERAND (NODE, 0) = VALUE

/* Whether the argument pack is "incomplete", meaning that more
   arguments can still be deduced. Incomplete argument packs are only
   used when the user has provided an explicit template argument list
   for a variadic function template. Some of the explicit template
   arguments will be placed into the beginning of the argument pack,
   but additional arguments might still be deduced.  */
#define ARGUMENT_PACK_INCOMPLETE_P(NODE)                                       \
  TREE_ADDRESSABLE (ARGUMENT_PACK_ARGS (NODE))

/* When ARGUMENT_PACK_INCOMPLETE_P, stores the explicit template
   arguments used to fill this pack.  */
#define ARGUMENT_PACK_EXPLICIT_ARGS(NODE) TREE_TYPE (ARGUMENT_PACK_ARGS (NODE))

/* In an ARGUMENT_PACK_SELECT, the argument pack from which an
   argument will be selected.  */
#define ARGUMENT_PACK_SELECT_FROM_PACK(NODE)                                   \
  (((struct tree_argument_pack_select *) ARGUMENT_PACK_SELECT_CHECK (NODE))    \
     ->argument_pack)

/* In an ARGUMENT_PACK_SELECT, the index of the argument we want to
   select.  */
#define ARGUMENT_PACK_SELECT_INDEX(NODE)                                       \
  (((struct tree_argument_pack_select *) ARGUMENT_PACK_SELECT_CHECK (NODE))    \
     ->index)

#define FOLD_EXPR_CHECK(NODE)                                                  \
  TREE_CHECK4 (NODE, UNARY_LEFT_FOLD_EXPR, UNARY_RIGHT_FOLD_EXPR,              \
	       BINARY_LEFT_FOLD_EXPR, BINARY_RIGHT_FOLD_EXPR)

#define BINARY_FOLD_EXPR_CHECK(NODE)                                           \
  TREE_CHECK2 (NODE, BINARY_LEFT_FOLD_EXPR, BINARY_RIGHT_FOLD_EXPR)

/* True if NODE is UNARY_FOLD_EXPR or a BINARY_FOLD_EXPR */
#define FOLD_EXPR_P(NODE)                                                      \
  (TREE_CODE (NODE) == UNARY_LEFT_FOLD_EXPR                                    \
   || TREE_CODE (NODE) == UNARY_RIGHT_FOLD_EXPR                                \
   || TREE_CODE (NODE) == BINARY_LEFT_FOLD_EXPR                                \
   || TREE_CODE (NODE) == BINARY_RIGHT_FOLD_EXPR)

/* True when NODE is a fold over a compound assignment operator. */
#define FOLD_EXPR_MODIFY_P(NODE) TREE_LANG_FLAG_0 (FOLD_EXPR_CHECK (NODE))

/* An INTEGER_CST containing the tree code of the folded operator. */
#define FOLD_EXPR_OP_RAW(NODE) TREE_OPERAND (FOLD_EXPR_CHECK (NODE), 0)

/* The tree code of the folded operator.  */
#define FOLD_EXPR_OP(NODE)                                                     \
  ((enum tree_code) TREE_INT_CST_LOW (FOLD_EXPR_OP_RAW (NODE)))

/* The expression containing an unexpanded parameter pack. */
#define FOLD_EXPR_PACK(NODE) TREE_OPERAND (FOLD_EXPR_CHECK (NODE), 1)

/* In a binary fold expression, the argument with no unexpanded
   parameter packs. */
#define FOLD_EXPR_INIT(NODE) TREE_OPERAND (BINARY_FOLD_EXPR_CHECK (NODE), 2)

/* In a FUNCTION_DECL, the saved auto-return pattern.  */
#define DECL_SAVED_AUTO_RETURN_TYPE(NODE)                                      \
  (LANG_DECL_FN_CHECK (FUNCTION_DECL_CHECK (NODE))->u.saved_auto_return_type)

/* True if NODE is an implicit INDIRECT_REF from convert_from_reference.  */
#define REFERENCE_REF_P(NODE)                                                  \
  (INDIRECT_REF_P (NODE) && TREE_TYPE (TREE_OPERAND (NODE, 0))                 \
   && TYPE_REF_P (TREE_TYPE (TREE_OPERAND ((NODE), 0))))

/* True iff this represents an lvalue being treated as an rvalue during return
   or throw as per [class.copy.elision].  */
#define IMPLICIT_RVALUE_P(NODE)                                                \
  TREE_LANG_FLAG_3 (TREE_CHECK2 ((NODE), NON_LVALUE_EXPR, STATIC_CAST_EXPR))

#define NEW_EXPR_USE_GLOBAL(NODE) TREE_LANG_FLAG_0 (NEW_EXPR_CHECK (NODE))
#define DELETE_EXPR_USE_GLOBAL(NODE) TREE_LANG_FLAG_0 (DELETE_EXPR_CHECK (NODE))
#define DELETE_EXPR_USE_VEC(NODE) TREE_LANG_FLAG_1 (DELETE_EXPR_CHECK (NODE))

#define CALL_OR_AGGR_INIT_CHECK(NODE)                                          \
  TREE_CHECK2 ((NODE), CALL_EXPR, AGGR_INIT_EXPR)

/* In a CALL_EXPR appearing in a template, true if Koenig lookup
   should be performed at instantiation time.  */
#define KOENIG_LOOKUP_P(NODE) TREE_LANG_FLAG_0 (CALL_EXPR_CHECK (NODE))

/* True if the arguments to NODE should be evaluated in left-to-right
   order regardless of PUSH_ARGS_REVERSED.  */
#define CALL_EXPR_ORDERED_ARGS(NODE)                                           \
  TREE_LANG_FLAG_3 (CALL_OR_AGGR_INIT_CHECK (NODE))

/* True if the arguments to NODE should be evaluated in right-to-left
   order regardless of PUSH_ARGS_REVERSED.  */
#define CALL_EXPR_REVERSE_ARGS(NODE)                                           \
  TREE_LANG_FLAG_5 (CALL_OR_AGGR_INIT_CHECK (NODE))

/* True if CALL_EXPR was written as an operator expression, not a function
   call.  */
#define CALL_EXPR_OPERATOR_SYNTAX(NODE)                                        \
  TREE_LANG_FLAG_6 (CALL_OR_AGGR_INIT_CHECK (NODE))

/* A TREE_LIST containing the result of phase 1 name lookup of the operator
   overloads that are pertinent to the dependent operator expression whose
   type is NODE.  Each TREE_PURPOSE is an IDENTIFIER_NODE and TREE_VALUE is
   the corresponding (possibly empty) lookup result.  The TREE_TYPE of the
   first TREE_LIST node points back to NODE.  */
#define DEPENDENT_OPERATOR_TYPE_SAVED_LOOKUPS(NODE)                            \
  TYPE_VALUES_RAW (DEPENDENT_OPERATOR_TYPE_CHECK (NODE))

/* Indicates whether a string literal has been parenthesized. Such
   usages are disallowed in certain circumstances.  */

#define PAREN_STRING_LITERAL_P(NODE) TREE_LANG_FLAG_0 (STRING_CST_CHECK (NODE))

/* Indicates whether a COMPONENT_REF or a SCOPE_REF has been parenthesized, an
   INDIRECT_REF comes from parenthesizing a _DECL, or a PAREN_EXPR identifies a
   parenthesized initializer relevant for decltype(auto).  Currently only set
   some of the time in C++14 mode.  */

#define REF_PARENTHESIZED_P(NODE)                                              \
  TREE_LANG_FLAG_2 (TREE_CHECK5 ((NODE), COMPONENT_REF, INDIRECT_REF,          \
				 SCOPE_REF, VIEW_CONVERT_EXPR, PAREN_EXPR))

/* Nonzero if this AGGR_INIT_EXPR provides for initialization via a
   constructor call, rather than an ordinary function call.  */
#define AGGR_INIT_VIA_CTOR_P(NODE)                                             \
  TREE_LANG_FLAG_0 (AGGR_INIT_EXPR_CHECK (NODE))

/* Nonzero if expanding this AGGR_INIT_EXPR should first zero-initialize
   the object.  */
#define AGGR_INIT_ZERO_FIRST(NODE)                                             \
  TREE_LANG_FLAG_2 (AGGR_INIT_EXPR_CHECK (NODE))

/* Nonzero means that the call is the jump from a thunk to the
   thunked-to function.  */
#define AGGR_INIT_FROM_THUNK_P(NODE)                                           \
  (AGGR_INIT_EXPR_CHECK (NODE)->base.protected_flag)

/* AGGR_INIT_EXPR accessors.  These are equivalent to the CALL_EXPR
   accessors, except for AGGR_INIT_EXPR_SLOT (which takes the place of
   CALL_EXPR_STATIC_CHAIN).  */

#define AGGR_INIT_EXPR_FN(NODE) TREE_OPERAND (AGGR_INIT_EXPR_CHECK (NODE), 1)
#define AGGR_INIT_EXPR_SLOT(NODE) TREE_OPERAND (AGGR_INIT_EXPR_CHECK (NODE), 2)
#define AGGR_INIT_EXPR_ARG(NODE, I)                                            \
  TREE_OPERAND (AGGR_INIT_EXPR_CHECK (NODE), (I) + 3)
#define aggr_init_expr_nargs(NODE) (VL_EXP_OPERAND_LENGTH (NODE) - 3)

/* AGGR_INIT_EXPR_ARGP returns a pointer to the argument vector for NODE.
   We can't use &AGGR_INIT_EXPR_ARG (NODE, 0) because that will complain if
   the argument count is zero when checking is enabled.  Instead, do
   the pointer arithmetic to advance past the 3 fixed operands in a
   AGGR_INIT_EXPR.  That produces a valid pointer to just past the end of
   the operand array, even if it's not valid to dereference it.  */
#define AGGR_INIT_EXPR_ARGP(NODE)                                              \
  (&(TREE_OPERAND (AGGR_INIT_EXPR_CHECK (NODE), 0)) + 3)

/* Iterate through each argument ARG of AGGR_INIT_EXPR CALL, using variable
   ITER (of type aggr_init_expr_arg_iterator) to hold the iteration state.  */
#define FOR_EACH_AGGR_INIT_EXPR_ARG(arg, iter, call)                           \
  for ((arg) = first_aggr_init_expr_arg ((call), &(iter)); (arg);              \
       (arg) = next_aggr_init_expr_arg (&(iter)))

/* VEC_INIT_EXPR accessors.  */
#define VEC_INIT_EXPR_SLOT(NODE) TREE_OPERAND (VEC_INIT_EXPR_CHECK (NODE), 0)
#define VEC_INIT_EXPR_INIT(NODE) TREE_OPERAND (VEC_INIT_EXPR_CHECK (NODE), 1)

/* Indicates that a VEC_INIT_EXPR is a potential constant expression.
   Only set when the current function is constexpr.  */
#define VEC_INIT_EXPR_IS_CONSTEXPR(NODE)                                       \
  TREE_LANG_FLAG_0 (VEC_INIT_EXPR_CHECK (NODE))

/* Indicates that a VEC_INIT_EXPR is expressing value-initialization.  */
#define VEC_INIT_EXPR_VALUE_INIT(NODE)                                         \
  TREE_LANG_FLAG_1 (VEC_INIT_EXPR_CHECK (NODE))

/* The condition under which this MUST_NOT_THROW_EXPR actually blocks
   exceptions.  NULL_TREE means 'true'.  */
#define MUST_NOT_THROW_COND(NODE)                                              \
  TREE_OPERAND (MUST_NOT_THROW_EXPR_CHECK (NODE), 1)

/* The TYPE_MAIN_DECL for a class template type is a TYPE_DECL, not a
   TEMPLATE_DECL.  This macro determines whether or not a given class
   type is really a template type, as opposed to an instantiation or
   specialization of one.  */
#define CLASSTYPE_IS_TEMPLATE(NODE)                                            \
  (CLASSTYPE_TEMPLATE_INFO (NODE) && !CLASSTYPE_USE_TEMPLATE (NODE)            \
   && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (NODE)))

/* The name used by the user to name the typename type.  Typically,
   this is an IDENTIFIER_NODE, and the same as the DECL_NAME on the
   corresponding TYPE_DECL.  However, this may also be a
   TEMPLATE_ID_EXPR if we had something like `typename X::Y<T>'.  */
#define TYPENAME_TYPE_FULLNAME(NODE)                                           \
  (TYPE_VALUES_RAW (TYPENAME_TYPE_CHECK (NODE)))

/* True if a TYPENAME_TYPE was declared as an "enum".  */
#define TYPENAME_IS_ENUM_P(NODE) (TREE_LANG_FLAG_0 (TYPENAME_TYPE_CHECK (NODE)))

/* True if a TYPENAME_TYPE was declared as a "class", "struct", or
   "union".  */
#define TYPENAME_IS_CLASS_P(NODE)                                              \
  (TREE_LANG_FLAG_1 (TYPENAME_TYPE_CHECK (NODE)))

/* True if a TYPENAME_TYPE is in the process of being resolved.  */
#define TYPENAME_IS_RESOLVING_P(NODE)                                          \
  (TREE_LANG_FLAG_2 (TYPENAME_TYPE_CHECK (NODE)))

/* [class.virtual]

   A class that declares or inherits a virtual function is called a
   polymorphic class.  */
#define TYPE_POLYMORPHIC_P(NODE) (TREE_LANG_FLAG_2 (NODE))

/* Nonzero if this class has a virtual function table pointer.  */
#define TYPE_CONTAINS_VPTR_P(NODE)                                             \
  (TYPE_POLYMORPHIC_P (NODE) || CLASSTYPE_VBASECLASSES (NODE))

/* Nonzero if NODE is a FUNCTION_DECL or VARIABLE_DECL (for a decl
   with namespace scope) declared in a local scope.  */
#define DECL_LOCAL_DECL_P(NODE)                                                \
  DECL_LANG_FLAG_0 (VAR_OR_FUNCTION_DECL_CHECK (NODE))

/* The namespace-scope decl a DECL_LOCAL_DECL_P aliases.  */
#define DECL_LOCAL_DECL_ALIAS(NODE)                                            \
  DECL_ACCESS ((gcc_checking_assert (DECL_LOCAL_DECL_P (NODE)), NODE))

/* Nonzero if NODE is the target for genericization of 'return' stmts
   in constructors/destructors of targetm.cxx.cdtor_returns_this targets.  */
#define LABEL_DECL_CDTOR(NODE) DECL_LANG_FLAG_2 (LABEL_DECL_CHECK (NODE))

/* True if NODE was declared with auto in its return type, but it has
   started compilation and so the return type might have been changed by
   return type deduction; its declared return type should be found in
   DECL_SAVED_AUTO_RETURN_TYPE (NODE).   */
#define FNDECL_USED_AUTO(NODE) TREE_LANG_FLAG_2 (FUNCTION_DECL_CHECK (NODE))

/* True if NODE is needed for a manifestly constant-evaluated expression.
   This doesn't especially need to be a flag, since currently it's only
   used for error recovery; if we run out of function flags it could move
   to an attribute.  */
#define FNDECL_MANIFESTLY_CONST_EVALUATED(NODE)                                \
  TREE_LANG_FLAG_4 (FUNCTION_DECL_CHECK (NODE))

/* True for artificial decls added for OpenMP privatized non-static
   data members.  */
#define DECL_OMP_PRIVATIZED_MEMBER(NODE)                                       \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))->u.base.anticipated_p)

/* Nonzero if NODE is an artificial FUNCTION_DECL for
   #pragma omp declare reduction.  */
#define DECL_OMP_DECLARE_REDUCTION_P(NODE)                                     \
  (LANG_DECL_FN_CHECK (DECL_COMMON_CHECK (NODE))->omp_declare_reduction_p)

/* Nonzero if DECL has been declared threadprivate by
   #pragma omp threadprivate.  */
#define CP_DECL_THREADPRIVATE_P(DECL)                                          \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (DECL))                                  \
     ->u.base.threadprivate_or_deleted_p)

/* Nonzero if NODE is a VAR_DECL which has been declared inline.  */
#define DECL_VAR_DECLARED_INLINE_P(NODE)                                       \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))                                  \
     ? DECL_LANG_SPECIFIC (NODE)->u.base.var_declared_inline_p                 \
     : false)
#define SET_DECL_VAR_DECLARED_INLINE_P(NODE)                                   \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))->u.base.var_declared_inline_p    \
   = true)

/* True if NODE is a constant variable with a value-dependent initializer.  */
#define DECL_DEPENDENT_INIT_P(NODE)                                            \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))                                  \
   && DECL_LANG_SPECIFIC (NODE)->u.base.dependent_init_p)
#define SET_DECL_DEPENDENT_INIT_P(NODE, X)                                     \
  (DECL_LANG_SPECIFIC (VAR_DECL_CHECK (NODE))->u.base.dependent_init_p = (X))

/* Nonzero if NODE is an artificial VAR_DECL for a C++17 structured binding
   declaration or one of VAR_DECLs for the user identifiers in it.  */
#define DECL_DECOMPOSITION_P(NODE)                                             \
  (VAR_P (NODE) && DECL_LANG_SPECIFIC (NODE)                                   \
     ? DECL_LANG_SPECIFIC (NODE)->u.base.selector == lds_decomp                \
     : false)

/* The underlying artificial VAR_DECL for structured binding.  */
#define DECL_DECOMP_BASE(NODE) (LANG_DECL_DECOMP_CHECK (NODE)->base)

/* Nonzero if NODE is an inline VAR_DECL.  In C++17, static data members
   declared with constexpr specifier are implicitly inline variables.  */
#define DECL_INLINE_VAR_P(NODE)                                                \
  (DECL_VAR_DECLARED_INLINE_P (NODE)                                           \
   || (cxx_dialect >= cxx17 && DECL_DECLARED_CONSTEXPR_P (NODE)                \
       && DECL_CLASS_SCOPE_P (NODE)))

/* Nonzero if DECL was declared with '= delete'.  */
#define DECL_DELETED_FN(DECL)                                                  \
  (LANG_DECL_FN_CHECK (DECL)->min.base.threadprivate_or_deleted_p)

/* Nonzero if DECL was declared with '= default' (maybe implicitly).  */
#define DECL_DEFAULTED_FN(DECL) (LANG_DECL_FN_CHECK (DECL)->defaulted_p)

/* Nonzero if DECL is explicitly defaulted in the class body.  */
#define DECL_DEFAULTED_IN_CLASS_P(DECL)                                        \
  (DECL_DEFAULTED_FN (DECL) && DECL_INITIALIZED_IN_CLASS_P (DECL))
/* Nonzero if DECL was defaulted outside the class body.  */
#define DECL_DEFAULTED_OUTSIDE_CLASS_P(DECL)                                   \
  (DECL_DEFAULTED_FN (DECL)                                                    \
   && !(DECL_ARTIFICIAL (DECL) || DECL_INITIALIZED_IN_CLASS_P (DECL)))

/* Record whether a typedef for type `int' was actually `signed int'.  */
#define C_TYPEDEF_EXPLICITLY_SIGNED(EXP) DECL_LANG_FLAG_1 (EXP)

/* Returns nonzero if DECL has external linkage, as specified by the
   language standard.  (This predicate may hold even when the
   corresponding entity is not actually given external linkage in the
   object file; see decl_linkage for details.)  */
#define DECL_EXTERNAL_LINKAGE_P(DECL) (decl_linkage (DECL) == lk_external)

/* Keep these codes in ascending code order.  */

#define INTEGRAL_CODE_P(CODE)                                                  \
  ((CODE) == ENUMERAL_TYPE || (CODE) == BOOLEAN_TYPE || (CODE) == INTEGER_TYPE)

/* [basic.fundamental]

   Types  bool, char, wchar_t, and the signed and unsigned integer types
   are collectively called integral types.

   Note that INTEGRAL_TYPE_P, as defined in tree.h, allows enumeration
   types as well, which is incorrect in C++.  Keep these checks in
   ascending code order.  */
#define CP_INTEGRAL_TYPE_P(TYPE)                                               \
  (TREE_CODE (TYPE) == BOOLEAN_TYPE || TREE_CODE (TYPE) == INTEGER_TYPE)

/* Returns true if TYPE is an integral or enumeration name.  Keep
   these checks in ascending code order.  */
#define INTEGRAL_OR_ENUMERATION_TYPE_P(TYPE)                                   \
  (TREE_CODE (TYPE) == ENUMERAL_TYPE || CP_INTEGRAL_TYPE_P (TYPE))

/* Returns true if TYPE is an integral or unscoped enumeration type.  */
#define INTEGRAL_OR_UNSCOPED_ENUMERATION_TYPE_P(TYPE)                          \
  (UNSCOPED_ENUM_P (TYPE) || CP_INTEGRAL_TYPE_P (TYPE))

/* True if the class type TYPE is a literal type.  */
#define CLASSTYPE_LITERAL_P(TYPE) (LANG_TYPE_CLASS_CHECK (TYPE)->is_literal)

/* [basic.fundamental]

   Integral and floating types are collectively called arithmetic
   types.

   As a GNU extension, we also accept complex types.

   Keep these checks in ascending code order.  */
#define ARITHMETIC_TYPE_P(TYPE)                                                \
  (RS_INTEGRAL_TYPE_P (TYPE) || TREE_CODE (TYPE) == REAL_TYPE                  \
   || TREE_CODE (TYPE) == COMPLEX_TYPE)

/* True iff TYPE is cv decltype(nullptr).  */
#define NULLPTR_TYPE_P(TYPE) (TREE_CODE (TYPE) == NULLPTR_TYPE)

/* [basic.types]

   Arithmetic types, enumeration types, pointer types,
   pointer-to-member types, and std::nullptr_t are collectively called
   scalar types.

   Keep these checks in ascending code order.  */
#define SCALAR_TYPE_P(TYPE)                                                    \
  (TREE_CODE (TYPE) == ENUMERAL_TYPE || ARITHMETIC_TYPE_P (TYPE)               \
   || TYPE_PTR_P (TYPE) || NULLPTR_TYPE_P (TYPE))

/* Determines whether this type is a C++0x scoped enumeration
   type. Scoped enumerations types are introduced via "enum class" or
   "enum struct", e.g.,

     enum class Color {
       Red, Green, Blue
     };

   Scoped enumeration types are different from normal (unscoped)
   enumeration types in several ways:

     - The enumerators of a scoped enumeration type are only available
       within the scope of the enumeration type and not in the
       enclosing scope. For example, the Red color can be referred to
       with "Color::Red" but not "Red".

     - Scoped enumerators and enumerations do not implicitly convert
       to integers or 'bool'.

     - The underlying type of the enum is well-defined.  */
#define SCOPED_ENUM_P(TYPE)                                                    \
  (TREE_CODE (TYPE) == ENUMERAL_TYPE && ENUM_IS_SCOPED (TYPE))

/* Determine whether this is an unscoped enumeration type.  */
#define UNSCOPED_ENUM_P(TYPE)                                                  \
  (TREE_CODE (TYPE) == ENUMERAL_TYPE && !ENUM_IS_SCOPED (TYPE))

/* Set the flag indicating whether an ENUMERAL_TYPE is a C++0x scoped
   enumeration type (1) or a normal (unscoped) enumeration type
   (0).  */
#define SET_SCOPED_ENUM_P(TYPE, VAL) (ENUM_IS_SCOPED (TYPE) = (VAL))

#define SET_OPAQUE_ENUM_P(TYPE, VAL) (ENUM_IS_OPAQUE (TYPE) = (VAL))

#define OPAQUE_ENUM_P(TYPE)                                                    \
  (TREE_CODE (TYPE) == ENUMERAL_TYPE && ENUM_IS_OPAQUE (TYPE))

/* Determines whether an ENUMERAL_TYPE has an explicit
   underlying type.  */
#define ENUM_FIXED_UNDERLYING_TYPE_P(NODE) (TYPE_LANG_FLAG_5 (NODE))

/* Returns the underlying type of the given enumeration type. The
   underlying type is determined in different ways, depending on the
   properties of the enum:

     - In C++0x, the underlying type can be explicitly specified, e.g.,

	 enum E1 : char { ... } // underlying type is char

     - In a C++0x scoped enumeration, the underlying type is int
       unless otherwises specified:

	 enum class E2 { ... } // underlying type is int

     - Otherwise, the underlying type is determined based on the
       values of the enumerators. In this case, the
       ENUM_UNDERLYING_TYPE will not be set until after the definition
       of the enumeration is completed by finish_enum.  */
#define ENUM_UNDERLYING_TYPE(TYPE) TREE_TYPE (ENUMERAL_TYPE_CHECK (TYPE))

/* [dcl.init.aggr]

   An aggregate is an array or a class with no user-provided
   constructors, no brace-or-equal-initializers for non-static data
   members, no private or protected non-static data members, no
   base classes, and no virtual functions.

   As an extension, we also treat vectors as aggregates.  Keep these
   checks in ascending code order.  */
#define CP_AGGREGATE_TYPE_P(TYPE)                                              \
  (gnu_vector_type_p (TYPE) || TREE_CODE (TYPE) == ARRAY_TYPE                  \
   || (CLASS_TYPE_P (TYPE) && COMPLETE_TYPE_P (TYPE)                           \
       && !CLASSTYPE_NON_AGGREGATE (TYPE)))

/* Nonzero for a class type means that the class type has a
   user-declared constructor.  */
#define TYPE_HAS_USER_CONSTRUCTOR(NODE) (TYPE_LANG_FLAG_1 (NODE))

/* Nonzero means that the FUNCTION_TYPE or METHOD_TYPE has a
   late-specified return type.  */
#define TYPE_HAS_LATE_RETURN_TYPE(NODE)                                        \
  (TYPE_LANG_FLAG_2 (FUNC_OR_METHOD_CHECK (NODE)))

/* When appearing in an INDIRECT_REF, it means that the tree structure
   underneath is actually a call to a constructor.  This is needed
   when the constructor must initialize local storage (which can
   be automatically destroyed), rather than allowing it to allocate
   space from the heap.

   When appearing in a SAVE_EXPR, it means that underneath
   is a call to a constructor.

   When appearing in a CONSTRUCTOR, the expression is an unconverted
   compound literal.

   When appearing in a FIELD_DECL, it means that this field
   has been duly initialized in its constructor.  */
#define TREE_HAS_CONSTRUCTOR(NODE) (TREE_LANG_FLAG_4 (NODE))

/* True if NODE is a brace-enclosed initializer.  */
#define BRACE_ENCLOSED_INITIALIZER_P(NODE)                                     \
  (TREE_CODE (NODE) == CONSTRUCTOR && TREE_TYPE (NODE) == init_list_type_node)

/* True if NODE is a compound-literal, i.e., a brace-enclosed
   initializer cast to a particular type.  This is mostly only set during
   template parsing; once the initializer has been digested into an actual
   value of the type, the expression is represented by a TARGET_EXPR.  */
#define COMPOUND_LITERAL_P(NODE)                                               \
  (TREE_CODE (NODE) == CONSTRUCTOR && TREE_HAS_CONSTRUCTOR (NODE))

#define EMPTY_CONSTRUCTOR_P(NODE)                                              \
  (TREE_CODE (NODE) == CONSTRUCTOR                                             \
   && vec_safe_is_empty (CONSTRUCTOR_ELTS (NODE))                              \
   && !TREE_HAS_CONSTRUCTOR (NODE))

/* True if NODE is a init-list used as a direct-initializer, i.e.
   B b{1,2}, not B b({1,2}) or B b = {1,2}.  */
#define CONSTRUCTOR_IS_DIRECT_INIT(NODE)                                       \
  (TREE_LANG_FLAG_0 (CONSTRUCTOR_CHECK (NODE)))

/* True if this CONSTRUCTOR is instantiation-dependent and needs to be
   substituted.  */
#define CONSTRUCTOR_IS_DEPENDENT(NODE)                                         \
  (TREE_LANG_FLAG_1 (CONSTRUCTOR_CHECK (NODE)))

/* True if this CONSTRUCTOR should not be used as a variable initializer
   because it was loaded from a constexpr variable with mutable fields.  */
#define CONSTRUCTOR_MUTABLE_POISON(NODE)                                       \
  (TREE_LANG_FLAG_2 (CONSTRUCTOR_CHECK (NODE)))

/* True if this typed CONSTRUCTOR represents C99 compound-literal syntax rather
   than C++11 functional cast syntax.  */
#define CONSTRUCTOR_C99_COMPOUND_LITERAL(NODE)                                 \
  (TREE_LANG_FLAG_3 (CONSTRUCTOR_CHECK (NODE)))

/* True if this CONSTRUCTOR contains PLACEHOLDER_EXPRs referencing the
   CONSTRUCTOR's type not nested inside another CONSTRUCTOR marked with
   CONSTRUCTOR_PLACEHOLDER_BOUNDARY.  */
#define CONSTRUCTOR_PLACEHOLDER_BOUNDARY(NODE)                                 \
  (TREE_LANG_FLAG_5 (CONSTRUCTOR_CHECK (NODE)))

#define DIRECT_LIST_INIT_P(NODE)                                               \
  (BRACE_ENCLOSED_INITIALIZER_P (NODE) && CONSTRUCTOR_IS_DIRECT_INIT (NODE))

/* True if this is a designated initializer (when we allow initializer-clauses
   mixed with designated-initializer-clauses set whenever there is at least
   one designated-initializer-clause), or a C99 designator.  */
#define CONSTRUCTOR_IS_DESIGNATED_INIT(NODE)                                   \
  (TREE_LANG_FLAG_6 (CONSTRUCTOR_CHECK (NODE)))

/* True if this CONSTRUCTOR comes from a parenthesized list of values, e.g.
   A(1, 2, 3).  */
#define CONSTRUCTOR_IS_PAREN_INIT(NODE)                                        \
  (CONSTRUCTOR_CHECK (NODE)->base.private_flag)

/* True if reshape_init built this sub-CONSTRUCTOR to undo the brace elision
   of the original CONSTRUCTOR.  This flag is used during C++20 aggregate
   CTAD.  */
#define CONSTRUCTOR_BRACES_ELIDED_P(NODE)                                      \
  (CONSTRUCTOR_CHECK (NODE)->base.protected_flag)

/* True if NODE represents a conversion for direct-initialization in a
   template.  Set by perform_implicit_conversion_flags.  */
#define IMPLICIT_CONV_EXPR_DIRECT_INIT(NODE)                                   \
  (TREE_LANG_FLAG_0 (IMPLICIT_CONV_EXPR_CHECK (NODE)))

/* True if NODE represents a dependent conversion of a non-type template
   argument.  Set by maybe_convert_nontype_argument.  */
#define IMPLICIT_CONV_EXPR_NONTYPE_ARG(NODE)                                   \
  (TREE_LANG_FLAG_1 (IMPLICIT_CONV_EXPR_CHECK (NODE)))

/* True if NODE represents a conversion for braced-init-list in a
   template.  Set by perform_implicit_conversion_flags.  */
#define IMPLICIT_CONV_EXPR_BRACED_INIT(NODE)                                   \
  (TREE_LANG_FLAG_2 (IMPLICIT_CONV_EXPR_CHECK (NODE)))

/* Nonzero means that an object of this type cannot be initialized using
   an initializer list.  */
#define CLASSTYPE_NON_AGGREGATE(NODE)                                          \
  (LANG_TYPE_CLASS_CHECK (NODE)->non_aggregate)
#define TYPE_NON_AGGREGATE_CLASS(NODE)                                         \
  (CLASS_TYPE_P (NODE) && CLASSTYPE_NON_AGGREGATE (NODE))

/* Nonzero if there is a non-trivial X::op=(cv X&) for this class.  */
#define TYPE_HAS_COMPLEX_COPY_ASSIGN(NODE)                                     \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_complex_copy_assign)

/* Nonzero if there is a non-trivial X::X(cv X&) for this class.  */
#define TYPE_HAS_COMPLEX_COPY_CTOR(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_complex_copy_ctor)

/* Nonzero if there is a non-trivial X::op=(X&&) for this class.  */
#define TYPE_HAS_COMPLEX_MOVE_ASSIGN(NODE)                                     \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_complex_move_assign)

/* Nonzero if there is a non-trivial X::X(X&&) for this class.  */
#define TYPE_HAS_COMPLEX_MOVE_CTOR(NODE)                                       \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_complex_move_ctor)

/* Nonzero if there is no trivial default constructor for this class.  */
#define TYPE_HAS_COMPLEX_DFLT(NODE)                                            \
  (LANG_TYPE_CLASS_CHECK (NODE)->has_complex_dflt)

/* Nonzero if TYPE has a trivial destructor.  From [class.dtor]:

     A destructor is trivial if it is an implicitly declared
     destructor and if:

       - all of the direct base classes of its class have trivial
	 destructors,

       - for all of the non-static data members of its class that are
	 of class type (or array thereof), each such class has a
	 trivial destructor.  */
#define TYPE_HAS_TRIVIAL_DESTRUCTOR(NODE)                                      \
  (!TYPE_HAS_NONTRIVIAL_DESTRUCTOR (NODE))

/* Nonzero for _TYPE node means that this type does not have a trivial
   destructor.  Therefore, destroying an object of this type will
   involve a call to a destructor.  This can apply to objects of
   ARRAY_TYPE if the type of the elements needs a destructor.  */
#define TYPE_HAS_NONTRIVIAL_DESTRUCTOR(NODE) (TYPE_LANG_FLAG_4 (NODE))

/* Nonzero for class type means that the default constructor is trivial.  */
#define TYPE_HAS_TRIVIAL_DFLT(NODE)                                            \
  (TYPE_HAS_DEFAULT_CONSTRUCTOR (NODE) && !TYPE_HAS_COMPLEX_DFLT (NODE))

/* Nonzero for class type means that copy initialization of this type can use
   a bitwise copy.  */
#define TYPE_HAS_TRIVIAL_COPY_CTOR(NODE)                                       \
  (TYPE_HAS_COPY_CTOR (NODE) && !TYPE_HAS_COMPLEX_COPY_CTOR (NODE))

/* Nonzero for class type means that assignment of this type can use
   a bitwise copy.  */
#define TYPE_HAS_TRIVIAL_COPY_ASSIGN(NODE)                                     \
  (TYPE_HAS_COPY_ASSIGN (NODE) && !TYPE_HAS_COMPLEX_COPY_ASSIGN (NODE))

/* Returns true if NODE is a pointer-to-data-member.  */
#define TYPE_PTRDATAMEM_P(NODE) (TREE_CODE (NODE) == OFFSET_TYPE)

/* Returns true if NODE is a pointer.  */
#define TYPE_PTR_P(NODE) (TREE_CODE (NODE) == POINTER_TYPE)

/* Returns true if NODE is a reference.  */
#define TYPE_REF_P(NODE) (TREE_CODE (NODE) == REFERENCE_TYPE)

/* Returns true if NODE is a pointer or a reference.  */
#define INDIRECT_TYPE_P(NODE) (TYPE_PTR_P (NODE) || TYPE_REF_P (NODE))

/* Returns true if NODE is an object type:

     [basic.types]

     An object type is a (possibly cv-qualified) type that is not a
     function type, not a reference type, and not a void type.

   Keep these checks in ascending order, for speed.  */
#define TYPE_OBJ_P(NODE)                                                       \
  (!TYPE_REF_P (NODE) && !VOID_TYPE_P (NODE) && !FUNC_OR_METHOD_TYPE_P (NODE))

/* Returns true if NODE is a pointer to an object.  Keep these checks
   in ascending tree code order.  */
#define TYPE_PTROB_P(NODE) (TYPE_PTR_P (NODE) && TYPE_OBJ_P (TREE_TYPE (NODE)))

/* Returns true if NODE is a reference to an object.  Keep these checks
   in ascending tree code order.  */
#define TYPE_REF_OBJ_P(NODE)                                                   \
  (TYPE_REF_P (NODE) && TYPE_OBJ_P (TREE_TYPE (NODE)))

/* Returns true if NODE is a pointer to an object, or a pointer to
   void.  Keep these checks in ascending tree code order.  */
#define TYPE_PTROBV_P(NODE)                                                    \
  (TYPE_PTR_P (NODE) && !FUNC_OR_METHOD_TYPE_P (TREE_TYPE (NODE)))

/* Returns true if NODE is a pointer to function type.  */
#define TYPE_PTRFN_P(NODE)                                                     \
  (TYPE_PTR_P (NODE) && TREE_CODE (TREE_TYPE (NODE)) == FUNCTION_TYPE)

/* Returns true if NODE is a reference to function type.  */
#define TYPE_REFFN_P(NODE)                                                     \
  (TYPE_REF_P (NODE) && TREE_CODE (TREE_TYPE (NODE)) == FUNCTION_TYPE)

/* Returns true if NODE is a pointer to member function type.  */
#define TYPE_PTRMEMFUNC_P(NODE)                                                \
  (TREE_CODE (NODE) == RECORD_TYPE && TYPE_PTRMEMFUNC_FLAG (NODE))

#define TYPE_PTRMEMFUNC_FLAG(NODE) (TYPE_LANG_FLAG_2 (RECORD_TYPE_CHECK (NODE)))

/* Returns true if NODE is a pointer-to-member.  */
#define TYPE_PTRMEM_P(NODE)                                                    \
  (TYPE_PTRDATAMEM_P (NODE) || TYPE_PTRMEMFUNC_P (NODE))

/* Returns true if NODE is a pointer or a pointer-to-member.  */
#define TYPE_PTR_OR_PTRMEM_P(NODE) (TYPE_PTR_P (NODE) || TYPE_PTRMEM_P (NODE))

/* Indicates when overload resolution may resolve to a pointer to
   member function. [expr.unary.op]/3 */
#define PTRMEM_OK_P(NODE)                                                      \
  TREE_LANG_FLAG_0 (TREE_CHECK3 ((NODE), ADDR_EXPR, OFFSET_REF, SCOPE_REF))

/* Get the POINTER_TYPE to the METHOD_TYPE associated with this
   pointer to member function.  TYPE_PTRMEMFUNC_P _must_ be true,
   before using this macro.  */
#define TYPE_PTRMEMFUNC_FN_TYPE(NODE)                                          \
  (cp_build_qualified_type (TREE_TYPE (TYPE_FIELDS (NODE)),                    \
			    cp_type_quals (NODE)))

/* As above, but can be used in places that want an lvalue at the expense
   of not necessarily having the correct cv-qualifiers.  */
#define TYPE_PTRMEMFUNC_FN_TYPE_RAW(NODE) (TREE_TYPE (TYPE_FIELDS (NODE)))

/* Returns `A' for a type like `int (A::*)(double)' */
#define TYPE_PTRMEMFUNC_OBJECT_TYPE(NODE)                                      \
  TYPE_METHOD_BASETYPE (TREE_TYPE (TYPE_PTRMEMFUNC_FN_TYPE (NODE)))

/* The canonical internal RECORD_TYPE from the POINTER_TYPE to
   METHOD_TYPE.  */
#define TYPE_PTRMEMFUNC_TYPE(NODE) TYPE_LANG_SLOT_1 (NODE)

/* For a pointer-to-member type of the form `T X::*', this is `X'.
   For a type like `void (X::*)() const', this type is `X', not `const
   X'.  To get at the `const X' you have to look at the
   TYPE_PTRMEM_POINTED_TO_TYPE; there, the first parameter will have
   type `const X*'.  */
#define TYPE_PTRMEM_CLASS_TYPE(NODE)                                           \
  (TYPE_PTRDATAMEM_P (NODE) ? TYPE_OFFSET_BASETYPE (NODE)                      \
			    : TYPE_PTRMEMFUNC_OBJECT_TYPE (NODE))

/* For a pointer-to-member type of the form `T X::*', this is `T'.  */
#define TYPE_PTRMEM_POINTED_TO_TYPE(NODE)                                      \
  (TYPE_PTRDATAMEM_P (NODE) ? TREE_TYPE (NODE)                                 \
			    : TREE_TYPE (TYPE_PTRMEMFUNC_FN_TYPE (NODE)))

/* For a pointer-to-member constant `X::Y' this is the RECORD_TYPE for
   `X'.  */
#define PTRMEM_CST_CLASS(NODE)                                                 \
  TYPE_PTRMEM_CLASS_TYPE (TREE_TYPE (PTRMEM_CST_CHECK (NODE)))

/* For a pointer-to-member constant `X::Y' this is the _DECL for
   `Y'.  */
#define PTRMEM_CST_MEMBER(NODE)                                                \
  (((ptrmem_cst_t) PTRMEM_CST_CHECK (NODE))->member)

/* For a pointer-to-member constant `X::Y' this is a location where
   the address of the member has been taken.  */
#define PTRMEM_CST_LOCATION(NODE)                                              \
  (((ptrmem_cst_t) PTRMEM_CST_CHECK (NODE))->locus)

/* The expression in question for a TYPEOF_TYPE.  */
#define TYPEOF_TYPE_EXPR(NODE) (TYPE_VALUES_RAW (TYPEOF_TYPE_CHECK (NODE)))

/* The type in question for an UNDERLYING_TYPE.  */
#define UNDERLYING_TYPE_TYPE(NODE)                                             \
  (TYPE_VALUES_RAW (UNDERLYING_TYPE_CHECK (NODE)))

/* The type in question for BASES.  */
#define BASES_TYPE(NODE) (TYPE_VALUES_RAW (BASES_CHECK (NODE)))

#define BASES_DIRECT(NODE) TREE_LANG_FLAG_0 (BASES_CHECK (NODE))

/* The expression in question for a DECLTYPE_TYPE.  */
#define DECLTYPE_TYPE_EXPR(NODE) (TYPE_VALUES_RAW (DECLTYPE_TYPE_CHECK (NODE)))

/* Whether the DECLTYPE_TYPE_EXPR of NODE was originally parsed as an
   id-expression or a member-access expression. When false, it was
   parsed as a full expression.  */
#define DECLTYPE_TYPE_ID_EXPR_OR_MEMBER_ACCESS_P(NODE)                         \
  (DECLTYPE_TYPE_CHECK (NODE))->type_common.string_flag

/* These flags indicate that we want different semantics from normal
   decltype: lambda capture just drops references,
   lambda proxies look through implicit dereference.  */
#define DECLTYPE_FOR_LAMBDA_CAPTURE(NODE)                                      \
  TREE_LANG_FLAG_0 (DECLTYPE_TYPE_CHECK (NODE))
#define DECLTYPE_FOR_LAMBDA_PROXY(NODE)                                        \
  TREE_LANG_FLAG_2 (DECLTYPE_TYPE_CHECK (NODE))
#define DECLTYPE_FOR_REF_CAPTURE(NODE)                                         \
  TREE_LANG_FLAG_3 (DECLTYPE_TYPE_CHECK (NODE))

/* Nonzero for VAR_DECL and FUNCTION_DECL node means that `extern' was
   specified in its declaration.  This can also be set for an
   erroneously declared PARM_DECL.  */
#define DECL_THIS_EXTERN(NODE)                                                 \
  DECL_LANG_FLAG_2 (VAR_FUNCTION_OR_PARM_DECL_CHECK (NODE))

/* Nonzero for VAR_DECL and FUNCTION_DECL node means that `static' was
   specified in its declaration.  This can also be set for an
   erroneously declared PARM_DECL.  */
#define DECL_THIS_STATIC(NODE)                                                 \
  DECL_LANG_FLAG_6 (VAR_FUNCTION_OR_PARM_DECL_CHECK (NODE))

/* Nonzero for FIELD_DECL node means that this field is a lambda capture
   field for an array of runtime bound.  */
#define DECL_VLA_CAPTURE_P(NODE) DECL_LANG_FLAG_1 (FIELD_DECL_CHECK (NODE))

/* Nonzero for PARM_DECL node means that this is an array function
   parameter, i.e, a[] rather than *a.  */
#define DECL_ARRAY_PARAMETER_P(NODE) DECL_LANG_FLAG_1 (PARM_DECL_CHECK (NODE))

/* Nonzero for a FIELD_DECL who's NSMDI is currently being
   instantiated.  */
#define DECL_INSTANTIATING_NSDMI_P(NODE)                                       \
  DECL_LANG_FLAG_2 (FIELD_DECL_CHECK (NODE))

/* Nonzero for FIELD_DECL node means that this field is a base class
   of the parent object, as opposed to a member field.  */
#define DECL_FIELD_IS_BASE(NODE) DECL_LANG_FLAG_6 (FIELD_DECL_CHECK (NODE))

/* Nonzero for FIELD_DECL node means that this field is a simple (no
   explicit initializer) lambda capture field, making it invisible to
   name lookup in unevaluated contexts.  */
#define DECL_NORMAL_CAPTURE_P(NODE) DECL_LANG_FLAG_7 (FIELD_DECL_CHECK (NODE))

/* Nonzero if TYPE is an anonymous union or struct type.  We have to use a
   flag for this because "A union for which objects or pointers are
   declared is not an anonymous union" [class.union].  */
#define ANON_AGGR_TYPE_P(NODE)                                                 \
  (CLASS_TYPE_P (NODE) && LANG_TYPE_CLASS_CHECK (NODE)->anon_aggr)
#define SET_ANON_AGGR_TYPE_P(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->anon_aggr = 1)

/* Nonzero if TYPE is an anonymous union type.  */
#define ANON_UNION_TYPE_P(NODE)                                                \
  (TREE_CODE (NODE) == UNION_TYPE && ANON_AGGR_TYPE_P (NODE))

/* For an ANON_AGGR_TYPE_P the single FIELD_DECL it is used with.  */
#define ANON_AGGR_TYPE_FIELD(NODE) (LANG_TYPE_CLASS_CHECK (NODE)->typeinfo_var)

/* Define fields and accessors for nodes representing declared names.  */

/* True if TYPE is an unnamed structured type with a typedef for
   linkage purposes.  In that case TYPE_NAME and TYPE_STUB_DECL of the
   MAIN-VARIANT are different. */
#define TYPE_WAS_UNNAMED(NODE)                                                 \
  (TYPE_NAME (TYPE_MAIN_VARIANT (NODE))                                        \
   != TYPE_STUB_DECL (TYPE_MAIN_VARIANT (NODE)))

/* C++: all of these are overloaded!  These apply only to TYPE_DECLs.  */

/* The format of each node in the DECL_FRIENDLIST is as follows:

   The TREE_PURPOSE will be the name of a function, i.e., an
   IDENTIFIER_NODE.  The TREE_VALUE will be itself a TREE_LIST, whose
   TREE_VALUEs are friends with the given name.  */
#define DECL_FRIENDLIST(NODE) (DECL_INITIAL (NODE))
#define FRIEND_NAME(LIST) (TREE_PURPOSE (LIST))
#define FRIEND_DECLS(LIST) (TREE_VALUE (LIST))

/* The DECL_ACCESS, if non-NULL, is a TREE_LIST.  The TREE_PURPOSE of
   each node is a type; the TREE_VALUE is the access granted for this
   DECL in that type.  The DECL_ACCESS is set by access declarations.
   For example, if a member that would normally be public in a
   derived class is made protected, then the derived class and the
   protected_access_node will appear in the DECL_ACCESS for the node.  */
#define DECL_ACCESS(NODE) (LANG_DECL_MIN_CHECK (NODE)->access)

/* Nonzero if the FUNCTION_DECL is a global constructor.  */
#define DECL_GLOBAL_CTOR_P(NODE) (LANG_DECL_FN_CHECK (NODE)->global_ctor_p)

/* Nonzero if the FUNCTION_DECL is a global destructor.  */
#define DECL_GLOBAL_DTOR_P(NODE) (LANG_DECL_FN_CHECK (NODE)->global_dtor_p)

/* Accessor macros for C++ template decl nodes.  */

/* The DECL_TEMPLATE_PARMS are a list.  The TREE_PURPOSE of each node
   is a INT_CST whose TREE_INT_CST_LOW indicates the level of the
   template parameters, with 1 being the outermost set of template
   parameters.  The TREE_VALUE is a vector, whose elements are the
   template parameters at each level.  Each element in the vector is a
   TREE_LIST, whose TREE_VALUE is a PARM_DECL (if the parameter is a
   non-type parameter), or a TYPE_DECL (if the parameter is a type
   parameter) or a TEMPLATE_DECL (if the parameter is a template
   parameter).  The TREE_PURPOSE is the default value, if any.  The
   TEMPLATE_PARM_INDEX for the parameter is available as the
   DECL_INITIAL (for a PARM_DECL) or as the TREE_TYPE (for a
   TYPE_DECL).

   FIXME: CONST_CAST_TREE is a hack that hopefully will go away after
   tree is converted to C++ class hiearchy.  */
#define DECL_TEMPLATE_PARMS(NODE)                                              \
  ((struct tree_template_decl *) CONST_CAST_TREE (TEMPLATE_DECL_CHECK (NODE))) \
    ->arguments
#define DECL_INNERMOST_TEMPLATE_PARMS(NODE)                                    \
  INNERMOST_TEMPLATE_PARMS (DECL_TEMPLATE_PARMS (NODE))
#define DECL_NTPARMS(NODE)                                                     \
  TREE_VEC_LENGTH (DECL_INNERMOST_TEMPLATE_PARMS (NODE))
/* For function, method, class-data templates.

   FIXME: CONST_CAST_TREE is a hack that hopefully will go away after
   tree is converted to C++ class hiearchy.  */
#define DECL_TEMPLATE_RESULT(NODE)                                             \
  ((struct tree_template_decl *) CONST_CAST_TREE (TEMPLATE_DECL_CHECK (NODE))) \
    ->result
/* For a function template at namespace scope, DECL_TEMPLATE_INSTANTIATIONS
   lists all instantiations and specializations of the function so that
   tsubst_friend_function can reassign them to another template if we find
   that the namespace-scope template is really a partial instantiation of a
   friend template.

   For a class template the DECL_TEMPLATE_INSTANTIATIONS lists holds
   all instantiations and specializations of the class type, including
   partial instantiations and partial specializations, so that if we
   explicitly specialize a partial instantiation we can walk the list
   in maybe_process_partial_specialization and reassign them or complain
   as appropriate.

   In both cases, the TREE_PURPOSE of each node contains the arguments
   used; the TREE_VALUE contains the generated variable.  The template
   arguments are always complete.  For example, given:

      template <class T> struct S1 {
	template <class U> struct S2 {};
	template <class U> struct S2<U*> {};
      };

   the record for the partial specialization will contain, as its
   argument list, { {T}, {U*} }, and will be on the
   DECL_TEMPLATE_INSTANTIATIONS list for `template <class T> template
   <class U> struct S1<T>::S2'.

   This list is not used for other templates.  */
#define DECL_TEMPLATE_INSTANTIATIONS(NODE)                                     \
  DECL_SIZE_UNIT (TEMPLATE_DECL_CHECK (NODE))

/* For a class template, this list contains the partial
   specializations of this template.  (Full specializations are not
   recorded on this list.)  The TREE_PURPOSE holds the arguments used
   in the partial specialization (e.g., for `template <class T> struct
   S<T*, int>' this will be `T*, int'.)  The arguments will also include
   any outer template arguments.  The TREE_VALUE holds the TEMPLATE_DECL
   for the partial specialization.  The TREE_TYPE is the _TYPE node for
   the partial specialization.

   This list is not used for other templates.  */
#define DECL_TEMPLATE_SPECIALIZATIONS(NODE)                                    \
  DECL_SIZE (TEMPLATE_DECL_CHECK (NODE))

/* Nonzero for a DECL which is actually a template parameter.  Keep
   these checks in ascending tree code order.   */
#define DECL_TEMPLATE_PARM_P(NODE)                                             \
  (DECL_LANG_FLAG_0 (NODE)                                                     \
   && (TREE_CODE (NODE) == CONST_DECL || TREE_CODE (NODE) == PARM_DECL         \
       || TREE_CODE (NODE) == TYPE_DECL || TREE_CODE (NODE) == TEMPLATE_DECL))

/* Nonzero for a raw template parameter node.  */
#define TEMPLATE_PARM_P(NODE)                                                  \
  (TREE_CODE (NODE) == TEMPLATE_TYPE_PARM                                      \
   || TREE_CODE (NODE) == TEMPLATE_TEMPLATE_PARM                               \
   || TREE_CODE (NODE) == TEMPLATE_PARM_INDEX)

/* Mark NODE as a template parameter.  */
#define SET_DECL_TEMPLATE_PARM_P(NODE) (DECL_LANG_FLAG_0 (NODE) = 1)

/* Nonzero if NODE is a template template parameter.  */
#define DECL_TEMPLATE_TEMPLATE_PARM_P(NODE)                                    \
  (TREE_CODE (NODE) == TEMPLATE_DECL && DECL_TEMPLATE_PARM_P (NODE))

/* Nonzero for a DECL that represents a function template.  */
#define DECL_FUNCTION_TEMPLATE_P(NODE)                                         \
  (TREE_CODE (NODE) == TEMPLATE_DECL                                           \
   && DECL_TEMPLATE_RESULT (NODE) != NULL_TREE                                 \
   && TREE_CODE (DECL_TEMPLATE_RESULT (NODE)) == FUNCTION_DECL)

/* Nonzero for a DECL that represents a class template or alias
   template.  */
#define DECL_TYPE_TEMPLATE_P(NODE)                                             \
  (TREE_CODE (NODE) == TEMPLATE_DECL                                           \
   && DECL_TEMPLATE_RESULT (NODE) != NULL_TREE                                 \
   && TREE_CODE (DECL_TEMPLATE_RESULT (NODE)) == TYPE_DECL)

/* Nonzero for a DECL that represents a class template.  */
#define DECL_CLASS_TEMPLATE_P(NODE)                                            \
  (DECL_TYPE_TEMPLATE_P (NODE)                                                 \
   && DECL_IMPLICIT_TYPEDEF_P (DECL_TEMPLATE_RESULT (NODE)))

/* Nonzero for a TEMPLATE_DECL that represents an alias template.  */
#define DECL_ALIAS_TEMPLATE_P(NODE)                                            \
  (DECL_TYPE_TEMPLATE_P (NODE)                                                 \
   && !DECL_ARTIFICIAL (DECL_TEMPLATE_RESULT (NODE)))

/* Nonzero for a NODE which declares a type.  */
#define DECL_DECLARES_TYPE_P(NODE)                                             \
  (TREE_CODE (NODE) == TYPE_DECL || DECL_TYPE_TEMPLATE_P (NODE))

/* Nonzero if NODE declares a function.  */
#define DECL_DECLARES_FUNCTION_P(NODE)                                         \
  (TREE_CODE (NODE) == FUNCTION_DECL || DECL_FUNCTION_TEMPLATE_P (NODE))

/* Nonzero if NODE is the typedef implicitly generated for a type when
   the type is declared.  In C++, `struct S {};' is roughly
   equivalent to `struct S {}; typedef struct S S;' in C.
   DECL_IMPLICIT_TYPEDEF_P will hold for the typedef indicated in this
   example.  In C++, there is a second implicit typedef for each
   class, called the injected-class-name, in the scope of `S' itself, so that
   you can say `S::S'.  DECL_SELF_REFERENCE_P will hold for that typedef.  */
#define DECL_IMPLICIT_TYPEDEF_P(NODE)                                          \
  (TREE_CODE (NODE) == TYPE_DECL && DECL_LANG_FLAG_2 (NODE))
#define SET_DECL_IMPLICIT_TYPEDEF_P(NODE) (DECL_LANG_FLAG_2 (NODE) = 1)
#define DECL_SELF_REFERENCE_P(NODE)                                            \
  (TREE_CODE (NODE) == TYPE_DECL && DECL_LANG_FLAG_4 (NODE))
#define SET_DECL_SELF_REFERENCE_P(NODE) (DECL_LANG_FLAG_4 (NODE) = 1)

/* A `primary' template is one that has its own template header and is not
   a partial specialization.  A member function of a class template is a
   template, but not primary.  A member template is primary.  Friend
   templates are primary, too.  */

/* Returns the primary template corresponding to these parameters.  */
#define TPARMS_PRIMARY_TEMPLATE(NODE) (TREE_TYPE (NODE))

#define DECL_PRIMARY_TEMPLATE(NODE)                                            \
  (TPARMS_PRIMARY_TEMPLATE (DECL_INNERMOST_TEMPLATE_PARMS (NODE)))

/* Returns nonzero if NODE is a primary template.  */
#define PRIMARY_TEMPLATE_P(NODE) (DECL_PRIMARY_TEMPLATE (NODE) == (NODE))

/* Nonzero iff NODE is a specialization of a template.  The value
   indicates the type of specializations:

     1=implicit instantiation

     2=partial or explicit specialization, e.g.:

	template <> int min<int> (int, int),

     3=explicit instantiation, e.g.:

	template int min<int> (int, int);

   Note that NODE will be marked as a specialization even if the
   template it is instantiating is not a primary template.  For
   example, given:

     template <typename T> struct O {
       void f();
       struct I {};
     };

   both O<int>::f and O<int>::I will be marked as instantiations.

   If DECL_USE_TEMPLATE is nonzero, then DECL_TEMPLATE_INFO will also
   be non-NULL.  */
#define DECL_USE_TEMPLATE(NODE) (DECL_LANG_SPECIFIC (NODE)->u.base.use_template)

/* Like DECL_USE_TEMPLATE, but for class types.  */
#define CLASSTYPE_USE_TEMPLATE(NODE)                                           \
  (LANG_TYPE_CLASS_CHECK (NODE)->use_template)

/* True if NODE is a specialization of a primary template.  */
#define CLASSTYPE_SPECIALIZATION_OF_PRIMARY_TEMPLATE_P(NODE)                   \
  (CLASS_TYPE_P (NODE) && CLASSTYPE_USE_TEMPLATE (NODE)                        \
   && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (NODE)))

#define DECL_TEMPLATE_INSTANTIATION(NODE) (DECL_USE_TEMPLATE (NODE) & 1)
#define CLASSTYPE_TEMPLATE_INSTANTIATION(NODE)                                 \
  (CLASSTYPE_USE_TEMPLATE (NODE) & 1)

#define DECL_TEMPLATE_SPECIALIZATION(NODE) (DECL_USE_TEMPLATE (NODE) == 2)
#define SET_DECL_TEMPLATE_SPECIALIZATION(NODE) (DECL_USE_TEMPLATE (NODE) = 2)

/* Returns true for an explicit or partial specialization of a class
   template.  */
#define CLASSTYPE_TEMPLATE_SPECIALIZATION(NODE)                                \
  (CLASSTYPE_USE_TEMPLATE (NODE) == 2)
#define SET_CLASSTYPE_TEMPLATE_SPECIALIZATION(NODE)                            \
  (CLASSTYPE_USE_TEMPLATE (NODE) = 2)

#define DECL_IMPLICIT_INSTANTIATION(NODE) (DECL_USE_TEMPLATE (NODE) == 1)
#define SET_DECL_IMPLICIT_INSTANTIATION(NODE) (DECL_USE_TEMPLATE (NODE) = 1)
#define CLASSTYPE_IMPLICIT_INSTANTIATION(NODE)                                 \
  (CLASSTYPE_USE_TEMPLATE (NODE) == 1)
#define SET_CLASSTYPE_IMPLICIT_INSTANTIATION(NODE)                             \
  (CLASSTYPE_USE_TEMPLATE (NODE) = 1)

#define DECL_EXPLICIT_INSTANTIATION(NODE) (DECL_USE_TEMPLATE (NODE) == 3)
#define SET_DECL_EXPLICIT_INSTANTIATION(NODE) (DECL_USE_TEMPLATE (NODE) = 3)
#define CLASSTYPE_EXPLICIT_INSTANTIATION(NODE)                                 \
  (CLASSTYPE_USE_TEMPLATE (NODE) == 3)
#define SET_CLASSTYPE_EXPLICIT_INSTANTIATION(NODE)                             \
  (CLASSTYPE_USE_TEMPLATE (NODE) = 3)

/* Nonzero if DECL is a friend function which is an instantiation
   from the point of view of the compiler, but not from the point of
   view of the language.  For example given:
      template <class T> struct S { friend void f(T) {}; };
   the declaration of `void f(int)' generated when S<int> is
   instantiated will not be a DECL_TEMPLATE_INSTANTIATION, but will be
   a DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION.  */
#define DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION(DECL)                        \
  (DECL_LANG_SPECIFIC (DECL) && DECL_TEMPLATE_INFO (DECL)                      \
   && !DECL_USE_TEMPLATE (DECL))

/* Nonzero if DECL is a function generated from a function 'temploid',
   i.e. template, member of class template, or dependent friend.  */
#define DECL_TEMPLOID_INSTANTIATION(DECL)                                      \
  (DECL_TEMPLATE_INSTANTIATION (DECL)                                          \
   || DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION (DECL))

/* Nonzero if DECL is either defined implicitly by the compiler or
   generated from a temploid.  */
#define DECL_GENERATED_P(DECL)                                                 \
  (DECL_TEMPLOID_INSTANTIATION (DECL) || DECL_DEFAULTED_FN (DECL))

/* Nonzero iff we are currently processing a declaration for an
   entity with its own template parameter list, and which is not a
   full specialization.  */
#define PROCESSING_REAL_TEMPLATE_DECL_P()                                      \
  (!processing_template_parmlist                                               \
   && current_template_depth > template_class_depth (current_scope ()))

/* Nonzero if this VAR_DECL or FUNCTION_DECL has already been
   instantiated, i.e. its definition has been generated from the
   pattern given in the template.  */
#define DECL_TEMPLATE_INSTANTIATED(NODE)                                       \
  DECL_LANG_FLAG_1 (VAR_OR_FUNCTION_DECL_CHECK (NODE))

/* We know what we're doing with this decl now.  */
#define DECL_INTERFACE_KNOWN(NODE) DECL_LANG_FLAG_5 (NODE)

/* DECL_EXTERNAL must be set on a decl until the decl is actually emitted,
   so that assemble_external will work properly.  So we have this flag to
   tell us whether the decl is really not external.

   This flag does not indicate whether or not the decl is defined in the
   current translation unit; it indicates whether or not we should emit the
   decl at the end of compilation if it is defined and needed.  */
#define DECL_NOT_REALLY_EXTERN(NODE)                                           \
  (DECL_LANG_SPECIFIC (NODE)->u.base.not_really_extern)

#define DECL_REALLY_EXTERN(NODE)                                               \
  (DECL_EXTERNAL (NODE)                                                        \
   && (!DECL_LANG_SPECIFIC (NODE) || !DECL_NOT_REALLY_EXTERN (NODE)))

/* A thunk is a stub function.

   A thunk is an alternate entry point for an ordinary FUNCTION_DECL.
   The address of the ordinary FUNCTION_DECL is given by the
   DECL_INITIAL, which is always an ADDR_EXPR whose operand is a
   FUNCTION_DECL.  The job of the thunk is to either adjust the this
   pointer before transferring control to the FUNCTION_DECL, or call
   FUNCTION_DECL and then adjust the result value. Note, the result
   pointer adjusting thunk must perform a call to the thunked
   function, (or be implemented via passing some invisible parameter
   to the thunked function, which is modified to perform the
   adjustment just before returning).

   A thunk may perform either, or both, of the following operations:

   o Adjust the this or result pointer by a constant offset.
   o Adjust the this or result pointer by looking up a vcall or vbase offset
     in the vtable.

   A this pointer adjusting thunk converts from a base to a derived
   class, and hence adds the offsets. A result pointer adjusting thunk
   converts from a derived class to a base, and hence subtracts the
   offsets.  If both operations are performed, then the constant
   adjustment is performed first for this pointer adjustment and last
   for the result pointer adjustment.

   The constant adjustment is given by THUNK_FIXED_OFFSET.  If the
   vcall or vbase offset is required, THUNK_VIRTUAL_OFFSET is
   used. For this pointer adjusting thunks, it is the vcall offset
   into the vtable.  For result pointer adjusting thunks it is the
   binfo of the virtual base to convert to.  Use that binfo's vbase
   offset.

   It is possible to have equivalent covariant thunks.  These are
   distinct virtual covariant thunks whose vbase offsets happen to
   have the same value.  THUNK_ALIAS is used to pick one as the
   canonical thunk, which will get all the this pointer adjusting
   thunks attached to it.  */

/* An integer indicating how many bytes should be subtracted from the
   this or result pointer when this function is called.  */
#define THUNK_FIXED_OFFSET(DECL)                                               \
  (DECL_LANG_SPECIFIC (THUNK_FUNCTION_CHECK (DECL))->u.fn.u5.fixed_offset)

/* A tree indicating how to perform the virtual adjustment. For a this
   adjusting thunk it is the number of bytes to be added to the vtable
   to find the vcall offset. For a result adjusting thunk, it is the
   binfo of the relevant virtual base.  If NULL, then there is no
   virtual adjust.  (The vptr is always located at offset zero from
   the this or result pointer.)  (If the covariant type is within the
   class hierarchy being laid out, the vbase index is not yet known
   at the point we need to create the thunks, hence the need to use
   binfos.)  */

#define THUNK_VIRTUAL_OFFSET(DECL)                                             \
  (LANG_DECL_MIN_CHECK (FUNCTION_DECL_CHECK (DECL))->access)

/* A thunk which is equivalent to another thunk.  */
#define THUNK_ALIAS(DECL)                                                      \
  (DECL_LANG_SPECIFIC (FUNCTION_DECL_CHECK (DECL))->u.min.template_info)

/* For thunk NODE, this is the FUNCTION_DECL thunked to.  It is
   possible for the target to be a thunk too.  */
#define THUNK_TARGET(NODE) (LANG_DECL_FN_CHECK (NODE)->befriending_classes)

/* True for a SCOPE_REF iff the "template" keyword was used to
   indicate that the qualified name denotes a template.  */
#define QUALIFIED_NAME_IS_TEMPLATE(NODE)                                       \
  (TREE_LANG_FLAG_1 (SCOPE_REF_CHECK (NODE)))

/* [coroutines]
 */

/* True if NODE is a co-routine FUNCTION_DECL.  */
#define DECL_COROUTINE_P(NODE)                                                 \
  (LANG_DECL_FN_CHECK (DECL_COMMON_CHECK (NODE))->coroutine_p)

/* For a FUNCTION_DECL of a coroutine, this holds the ACTOR helper function
   decl.  */
#define DECL_ACTOR_FN(NODE) (coro_get_actor_function ((NODE)))

/* For a FUNCTION_DECL of a coroutine, this holds the DESTROY helper function
  decl.  */
#define DECL_DESTROY_FN(NODE) (coro_get_destroy_function ((NODE)))

/* For a FUNCTION_DECL of a coroutine helper (ACTOR or DESTROY), this points
   back to the original (ramp) function.  */
#define DECL_RAMP_FN(NODE) (coro_get_ramp_function (NODE))

/* True for an OMP_ATOMIC that has dependent parameters.  These are stored
   as an expr in operand 1, and integer_zero_node or clauses in operand 0.  */
#define OMP_ATOMIC_DEPENDENT_P(NODE)                                           \
  (TREE_CODE (TREE_OPERAND (OMP_ATOMIC_CHECK (NODE), 0)) == INTEGER_CST        \
   || TREE_CODE (TREE_OPERAND (OMP_ATOMIC_CHECK (NODE), 0)) == OMP_CLAUSE)

/* Used while gimplifying continue statements bound to OMP_FOR nodes.  */
#define OMP_FOR_GIMPLIFYING_P(NODE)                                            \
  (TREE_LANG_FLAG_0 (OMP_LOOPING_CHECK (NODE)))

/* A language-specific token attached to the OpenMP data clauses to
   hold code (or code fragments) related to ctors, dtors, and op=.
   See semantics.cc for details.  */
#define CP_OMP_CLAUSE_INFO(NODE)                                               \
  TREE_TYPE (                                                                  \
    OMP_CLAUSE_RANGE_CHECK (NODE, OMP_CLAUSE_PRIVATE, OMP_CLAUSE__CONDTEMP_))

/* Nonzero if this transaction expression's body contains statements.  */
#define TRANSACTION_EXPR_IS_STMT(NODE)                                         \
  TREE_LANG_FLAG_0 (TRANSACTION_EXPR_CHECK (NODE))

/* These macros provide convenient access to the various _STMT nodes
   created when parsing template declarations.  */
#define TRY_STMTS(NODE) TREE_OPERAND (TRY_BLOCK_CHECK (NODE), 0)
#define TRY_HANDLERS(NODE) TREE_OPERAND (TRY_BLOCK_CHECK (NODE), 1)

#define EH_SPEC_STMTS(NODE) TREE_OPERAND (EH_SPEC_BLOCK_CHECK (NODE), 0)
#define EH_SPEC_RAISES(NODE) TREE_OPERAND (EH_SPEC_BLOCK_CHECK (NODE), 1)

#define USING_STMT_NAMESPACE(NODE) TREE_OPERAND (USING_STMT_CHECK (NODE), 0)

/* Nonzero if this try block is a function try block.  */
#define FN_TRY_BLOCK_P(NODE) TREE_LANG_FLAG_3 (TRY_BLOCK_CHECK (NODE))
#define HANDLER_PARMS(NODE) TREE_OPERAND (HANDLER_CHECK (NODE), 0)
#define HANDLER_BODY(NODE) TREE_OPERAND (HANDLER_CHECK (NODE), 1)
#define HANDLER_TYPE(NODE) TREE_TYPE (HANDLER_CHECK (NODE))

/* CLEANUP_STMT accessors.  The statement(s) covered, the cleanup to run
   and the VAR_DECL for which this cleanup exists.  */
#define CLEANUP_BODY(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 0)
#define CLEANUP_EXPR(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 1)
#define CLEANUP_DECL(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 2)

/* IF_STMT accessors. These give access to the condition of the if
   statement, the then block of the if statement, and the else block
   of the if statement if it exists.  */
#define IF_COND(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 0)
#define THEN_CLAUSE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 1)
#define ELSE_CLAUSE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 2)
#define IF_SCOPE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 3)
#define IF_STMT_CONSTEXPR_P(NODE) TREE_LANG_FLAG_0 (IF_STMT_CHECK (NODE))
#define IF_STMT_CONSTEVAL_P(NODE) TREE_LANG_FLAG_2 (IF_STMT_CHECK (NODE))

/* Like PACK_EXPANSION_EXTRA_ARGS, for constexpr if.  IF_SCOPE is used while
   building an IF_STMT; IF_STMT_EXTRA_ARGS is used after it is complete.  */
#define IF_STMT_EXTRA_ARGS(NODE) IF_SCOPE (NODE)

/* RANGE_FOR_STMT accessors. These give access to the declarator,
   expression, body, and scope of the statement, respectively.  */
#define RANGE_FOR_DECL(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 0)
#define RANGE_FOR_EXPR(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 1)
#define RANGE_FOR_BODY(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 2)
#define RANGE_FOR_SCOPE(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 3)
#define RANGE_FOR_UNROLL(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 4)
#define RANGE_FOR_INIT_STMT(NODE) TREE_OPERAND (RANGE_FOR_STMT_CHECK (NODE), 5)
#define RANGE_FOR_IVDEP(NODE) TREE_LANG_FLAG_6 (RANGE_FOR_STMT_CHECK (NODE))

/* STMT_EXPR accessor.  */
#define STMT_EXPR_STMT(NODE) TREE_OPERAND (STMT_EXPR_CHECK (NODE), 0)

/* EXPR_STMT accessor. This gives the expression associated with an
   expression statement.  */
#define EXPR_STMT_EXPR(NODE) TREE_OPERAND (EXPR_STMT_CHECK (NODE), 0)

/* True if this TARGET_EXPR was created by build_cplus_new, and so we can
   discard it if it isn't useful.  */
#define TARGET_EXPR_IMPLICIT_P(NODE) TREE_LANG_FLAG_0 (TARGET_EXPR_CHECK (NODE))

/* True if this TARGET_EXPR is the result of list-initialization of a
   temporary.  */
#define TARGET_EXPR_LIST_INIT_P(NODE)                                          \
  TREE_LANG_FLAG_1 (TARGET_EXPR_CHECK (NODE))

/* True if this TARGET_EXPR expresses direct-initialization of an object
   to be named later.  */
#define TARGET_EXPR_DIRECT_INIT_P(NODE)                                        \
  TREE_LANG_FLAG_2 (TARGET_EXPR_CHECK (NODE))

/* True if NODE is a TARGET_EXPR that just expresses a copy of its INITIAL; if
   the initializer has void type, it's doing something more complicated.  */
#define SIMPLE_TARGET_EXPR_P(NODE)                                             \
  (TREE_CODE (NODE) == TARGET_EXPR && TARGET_EXPR_INITIAL (NODE)               \
   && !VOID_TYPE_P (TREE_TYPE (TARGET_EXPR_INITIAL (NODE))))

/* True if EXPR expresses direct-initialization of a TYPE.  */
#define DIRECT_INIT_EXPR_P(TYPE, EXPR)                                         \
  (TREE_CODE (EXPR) == TARGET_EXPR && TREE_LANG_FLAG_2 (EXPR)                  \
   && same_type_ignoring_top_level_qualifiers_p (TYPE, TREE_TYPE (EXPR)))

/* True if this CONVERT_EXPR is for a conversion to virtual base in
   an NSDMI, and should be re-evaluated when used in a constructor.  */
#define CONVERT_EXPR_VBASE_PATH(NODE)                                          \
  TREE_LANG_FLAG_0 (CONVERT_EXPR_CHECK (NODE))

/* True if SIZEOF_EXPR argument is type.  */
#define SIZEOF_EXPR_TYPE_P(NODE) TREE_LANG_FLAG_0 (SIZEOF_EXPR_CHECK (NODE))

/* True if the ALIGNOF_EXPR was spelled "alignof".  */
#define ALIGNOF_EXPR_STD_P(NODE) TREE_LANG_FLAG_0 (ALIGNOF_EXPR_CHECK (NODE))

/* OMP_DEPOBJ accessors. These give access to the depobj expression of the
   #pragma omp depobj directive and the clauses, respectively.  If
   OMP_DEPOBJ_CLAUSES is INTEGER_CST, it is instead the update clause kind
   or OMP_CLAUSE_DEPEND_LAST for destroy clause.  */
#define OMP_DEPOBJ_DEPOBJ(NODE) TREE_OPERAND (OMP_DEPOBJ_CHECK (NODE), 0)
#define OMP_DEPOBJ_CLAUSES(NODE) TREE_OPERAND (OMP_DEPOBJ_CHECK (NODE), 1)

/* Here's where we control how name mangling takes place.  */

/* Cannot use '$' up front, because this confuses gdb
   (names beginning with '$' are gdb-local identifiers).

   Note that all forms in which the '$' is significant are long enough
   for direct indexing (meaning that if we know there is a '$'
   at a particular location, we can index into the string at
   any other location that provides distinguishing characters).  */

/* Define NO_DOT_IN_LABEL in your favorite tm file if your assembler
   doesn't allow '.' in symbol names.  */
#ifndef NO_DOT_IN_LABEL

#define JOINER '.'
#define JOIN_STR "."

#define AUTO_TEMP_NAME "_.tmp_"
#define VFIELD_BASE ".vf"
#define VFIELD_NAME "_vptr."
#define VFIELD_NAME_FORMAT "_vptr.%s"

#else /* NO_DOT_IN_LABEL */

#ifndef NO_DOLLAR_IN_LABEL

#define JOINER '$'
#define JOIN_STR "$"

#define AUTO_TEMP_NAME "_$tmp_"
#define VFIELD_BASE "$vf"
#define VFIELD_NAME "_vptr$"
#define VFIELD_NAME_FORMAT "_vptr$%s"

#else /* NO_DOLLAR_IN_LABEL */

#define JOIN_STR "_"

#define VTABLE_NAME "__vt_"
#define VTABLE_NAME_P(ID_NODE)                                                 \
  (!strncmp (IDENTIFIER_POINTER (ID_NODE), VTABLE_NAME,                        \
	     sizeof (VTABLE_NAME) - 1))
#define VFIELD_BASE "__vfb"
#define VFIELD_NAME "__vptr_"
#define VFIELD_NAME_P(ID_NODE)                                                 \
  (!strncmp (IDENTIFIER_POINTER (ID_NODE), VFIELD_NAME,                        \
	     sizeof (VFIELD_NAME) - 1))
#define VFIELD_NAME_FORMAT "__vptr_%s"

#endif /* NO_DOLLAR_IN_LABEL */
#endif /* NO_DOT_IN_LABEL */

#define UDLIT_OP_ANSI_PREFIX "operator\"\""
#define UDLIT_OP_ANSI_FORMAT UDLIT_OP_ANSI_PREFIX "%s"
#define UDLIT_OP_MANGLED_PREFIX "li"
#define UDLIT_OP_MANGLED_FORMAT UDLIT_OP_MANGLED_PREFIX "%s"
#define UDLIT_OPER_P(ID_NODE)                                                  \
  (!strncmp (IDENTIFIER_POINTER (ID_NODE), UDLIT_OP_ANSI_PREFIX,               \
	     sizeof (UDLIT_OP_ANSI_PREFIX) - 1))
#define UDLIT_OP_SUFFIX(ID_NODE)                                               \
  (IDENTIFIER_POINTER (ID_NODE) + sizeof (UDLIT_OP_ANSI_PREFIX) - 1)

#if !defined(NO_DOLLAR_IN_LABEL) || !defined(NO_DOT_IN_LABEL)

#define VTABLE_NAME_P(ID_NODE)                                                 \
  (IDENTIFIER_POINTER (ID_NODE)[1] == 'v'                                      \
   && IDENTIFIER_POINTER (ID_NODE)[2] == 't'                                   \
   && IDENTIFIER_POINTER (ID_NODE)[3] == JOINER)

#define VFIELD_NAME_P(ID_NODE)                                                 \
  (!strncmp (IDENTIFIER_POINTER (ID_NODE), VFIELD_NAME,                        \
	     sizeof (VFIELD_NAME) - 1))

#endif /* !defined(NO_DOLLAR_IN_LABEL) || !defined(NO_DOT_IN_LABEL) */

/* These are uses as bits in flags passed to various functions to
   control their behavior.  Despite the LOOKUP_ prefix, many of these
   do not control name lookup.  ??? Functions using these flags should
   probably be modified to accept explicit boolean flags for the
   behaviors relevant to them.  */
/* Check for access violations.  */
#define LOOKUP_PROTECT (1 << 0)
#define LOOKUP_NORMAL (LOOKUP_PROTECT)
/* Even if the function found by lookup is a virtual function, it
   should be called directly.  */
#define LOOKUP_NONVIRTUAL (1 << 1)
/* Non-converting (i.e., "explicit") constructors are not tried.  This flag
   indicates that we are not performing direct-initialization.  */
#define LOOKUP_ONLYCONVERTING (1 << 2)
#define LOOKUP_IMPLICIT (LOOKUP_NORMAL | LOOKUP_ONLYCONVERTING)
/* If a temporary is created, it should be created so that it lives
   as long as the current variable bindings; otherwise it only lives
   until the end of the complete-expression.  It also forces
   direct-initialization in cases where other parts of the compiler
   have already generated a temporary, such as reference
   initialization and the catch parameter.  */
#define DIRECT_BIND (1 << 3)
/* We're performing a user-defined conversion, so more user-defined
   conversions are not permitted (only built-in conversions).  */
#define LOOKUP_NO_CONVERSION (1 << 4)
/* The user has explicitly called a destructor.  (Therefore, we do
   not need to check that the object is non-NULL before calling the
   destructor.)  */
#define LOOKUP_DESTRUCTOR (1 << 5)
/* Do not permit references to bind to temporaries.  */
#define LOOKUP_NO_TEMP_BIND (1 << 6)
/* We're trying to treat an lvalue as an rvalue.  */
/* FIXME remove when we extend the P1825 semantics to all standard modes, the
   C++20 approach uses IMPLICIT_RVALUE_P instead.  */
#define LOOKUP_PREFER_RVALUE (LOOKUP_NO_TEMP_BIND << 1)
/* We're inside an init-list, so narrowing conversions are ill-formed.  */
#define LOOKUP_NO_NARROWING (LOOKUP_PREFER_RVALUE << 1)
/* We're looking up a constructor for list-initialization.  */
#define LOOKUP_LIST_INIT_CTOR (LOOKUP_NO_NARROWING << 1)
/* This is the first parameter of a copy constructor.  */
#define LOOKUP_COPY_PARM (LOOKUP_LIST_INIT_CTOR << 1)
/* We only want to consider list constructors.  */
#define LOOKUP_LIST_ONLY (LOOKUP_COPY_PARM << 1)
/* Return after determining which function to call and checking access.
   Used by sythesized_method_walk to determine which functions will
   be called to initialize subobjects, in order to determine exception
   specification and possible implicit delete.
   This is kind of a hack, but exiting early avoids problems with trying
   to perform argument conversions when the class isn't complete yet.  */
#define LOOKUP_SPECULATIVE (LOOKUP_LIST_ONLY << 1)
/* Used by calls from defaulted functions to limit the overload set to avoid
   cycles trying to declare them (core issue 1092).  */
#define LOOKUP_DEFAULTED (LOOKUP_SPECULATIVE << 1)
/* Used in calls to store_init_value to suppress its usual call to
   digest_init.  */
#define LOOKUP_ALREADY_DIGESTED (LOOKUP_DEFAULTED << 1)
/* Like LOOKUP_NO_TEMP_BIND, but also prevent binding to xvalues.  */
#define LOOKUP_NO_RVAL_BIND (LOOKUP_ALREADY_DIGESTED << 1)
/* Used by case_conversion to disregard non-integral conversions.  */
#define LOOKUP_NO_NON_INTEGRAL (LOOKUP_NO_RVAL_BIND << 1)
/* Used for delegating constructors in order to diagnose self-delegation.  */
#define LOOKUP_DELEGATING_CONS (LOOKUP_NO_NON_INTEGRAL << 1)
/* Allow initialization of a flexible array members.  */
#define LOOKUP_ALLOW_FLEXARRAY_INIT (LOOKUP_DELEGATING_CONS << 1)
/* We're looking for either a rewritten comparison operator candidate or the
   operator to use on the former's result.  We distinguish between the two by
   knowing that comparisons other than == and <=> must be the latter, as must
   a <=> expression trying to rewrite to <=> without reversing.  */
#define LOOKUP_REWRITTEN (LOOKUP_ALLOW_FLEXARRAY_INIT << 1)
/* Reverse the order of the two arguments for comparison rewriting.  First we
   swap the arguments in add_operator_candidates, then we swap the conversions
   in add_candidate (so that they correspond to the original order of the
   args), then we swap the conversions back in build_new_op_1 (so they
   correspond to the order of the args in the candidate).  */
#define LOOKUP_REVERSED (LOOKUP_REWRITTEN << 1)
/* We're initializing an aggregate from a parenthesized list of values.  */
#define LOOKUP_AGGREGATE_PAREN_INIT (LOOKUP_REVERSED << 1)

/* These flags are used by the conversion code.
   CONV_IMPLICIT   :  Perform implicit conversions (standard and user-defined).
   CONV_STATIC     :  Perform the explicit conversions for static_cast.
   CONV_CONST      :  Perform the explicit conversions for const_cast.
   CONV_REINTERPRET:  Perform the explicit conversions for reinterpret_cast.
   CONV_PRIVATE    :  Perform upcasts to private bases.
   CONV_FORCE_TEMP :  Require a new temporary when converting to the same
		      aggregate type.  */

#define CONV_IMPLICIT 1
#define CONV_STATIC 2
#define CONV_CONST 4
#define CONV_REINTERPRET 8
#define CONV_PRIVATE 16
#define CONV_FORCE_TEMP 32
#define CONV_FOLD 64
#define CONV_OLD_CONVERT                                                       \
  (CONV_IMPLICIT | CONV_STATIC | CONV_CONST | CONV_REINTERPRET)
#define CONV_C_CAST                                                            \
  (CONV_IMPLICIT | CONV_STATIC | CONV_CONST | CONV_REINTERPRET | CONV_PRIVATE  \
   | CONV_FORCE_TEMP)
#define CONV_BACKEND_CONVERT (CONV_OLD_CONVERT | CONV_FOLD)

/* Used by build_expr_type_conversion to indicate which types are
   acceptable as arguments to the expression under consideration.  */

#define WANT_INT 1		  /* integer types, including bool */
#define WANT_FLOAT 2		  /* floating point types */
#define WANT_ENUM 4		  /* enumerated types */
#define WANT_POINTER 8		  /* pointer types */
#define WANT_NULL 16		  /* null pointer constant */
#define WANT_VECTOR_OR_COMPLEX 32 /* vector or complex types */
#define WANT_ARITH (WANT_INT | WANT_FLOAT | WANT_VECTOR_OR_COMPLEX)

/* Used with comptypes, and related functions, to guide type
   comparison.  */

#define COMPARE_STRICT                                                         \
  0 /* Just check if the types are the                                         \
       same.  */
#define COMPARE_BASE                                                           \
  1 /* Check to see if the second type is                                      \
       derived from the first.  */
#define COMPARE_DERIVED                                                        \
  2 /* Like COMPARE_BASE, but in                                               \
       reverse.  */
#define COMPARE_REDECLARATION                                                  \
  4 /* The comparison is being done when                                       \
       another declaration of an existing                                      \
       entity is seen.  */
#define COMPARE_STRUCTURAL                                                     \
  8 /* The comparison is intended to be                                        \
       structural. The actual comparison                                       \
       will be identical to                                                    \
       COMPARE_STRICT.  */

/* Used with start function.  */
#define SF_DEFAULT 0 /* No flags.  */
#define SF_PRE_PARSED                                                          \
  1 /* The function declaration has                                            \
       already been parsed.  */
#define SF_INCLASS_INLINE                                                      \
  2 /* The function is an inline, defined                                      \
       in the class body.  */

/* Used with start_decl's initialized parameter.  */
#define SD_UNINITIALIZED 0
#define SD_INITIALIZED 1
/* Like SD_INITIALIZED, but also mark the new decl as DECL_DECOMPOSITION_P.  */
#define SD_DECOMPOSITION 2
#define SD_DEFAULTED 3
#define SD_DELETED 4

/* Returns nonzero iff TYPE1 and TYPE2 are the same type, or if TYPE2
   is derived from TYPE1, or if TYPE2 is a pointer (reference) to a
   class derived from the type pointed to (referred to) by TYPE1.  */
#define same_or_base_type_p(TYPE1, TYPE2)                                      \
  comptypes ((TYPE1), (TYPE2), COMPARE_BASE)

/* These macros are used to access a TEMPLATE_PARM_INDEX.  */
#define TEMPLATE_PARM_INDEX_CAST(NODE)                                         \
  ((template_parm_index *) TEMPLATE_PARM_INDEX_CHECK (NODE))
#define TEMPLATE_PARM_IDX(NODE) (TEMPLATE_PARM_INDEX_CAST (NODE)->index)
#define TEMPLATE_PARM_LEVEL(NODE) (TEMPLATE_PARM_INDEX_CAST (NODE)->level)
#define TEMPLATE_PARM_DESCENDANTS(NODE) (TREE_CHAIN (NODE))
#define TEMPLATE_PARM_ORIG_LEVEL(NODE)                                         \
  (TEMPLATE_PARM_INDEX_CAST (NODE)->orig_level)
#define TEMPLATE_PARM_DECL(NODE) (TEMPLATE_PARM_INDEX_CAST (NODE)->decl)
#define TEMPLATE_PARM_PARAMETER_PACK(NODE)                                     \
  (TREE_LANG_FLAG_0 (TEMPLATE_PARM_INDEX_CHECK (NODE)))

/* These macros are for accessing the fields of TEMPLATE_TYPE_PARM,
   TEMPLATE_TEMPLATE_PARM and BOUND_TEMPLATE_TEMPLATE_PARM nodes.  */
#define TEMPLATE_TYPE_PARM_INDEX(NODE)                                         \
  (TYPE_VALUES_RAW (TREE_CHECK3 ((NODE), TEMPLATE_TYPE_PARM,                   \
				 TEMPLATE_TEMPLATE_PARM,                       \
				 BOUND_TEMPLATE_TEMPLATE_PARM)))
#define TEMPLATE_TYPE_IDX(NODE)                                                \
  (TEMPLATE_PARM_IDX (TEMPLATE_TYPE_PARM_INDEX (NODE)))
#define TEMPLATE_TYPE_LEVEL(NODE)                                              \
  (TEMPLATE_PARM_LEVEL (TEMPLATE_TYPE_PARM_INDEX (NODE)))
#define TEMPLATE_TYPE_ORIG_LEVEL(NODE)                                         \
  (TEMPLATE_PARM_ORIG_LEVEL (TEMPLATE_TYPE_PARM_INDEX (NODE)))
#define TEMPLATE_TYPE_DECL(NODE)                                               \
  (TEMPLATE_PARM_DECL (TEMPLATE_TYPE_PARM_INDEX (NODE)))
#define TEMPLATE_TYPE_PARAMETER_PACK(NODE)                                     \
  (TEMPLATE_PARM_PARAMETER_PACK (TEMPLATE_TYPE_PARM_INDEX (NODE)))

/* True iff this TEMPLATE_TYPE_PARM represents decltype(auto).  */
#define AUTO_IS_DECLTYPE(NODE)                                                 \
  (TYPE_LANG_FLAG_5 (TEMPLATE_TYPE_PARM_CHECK (NODE)))

/* These constants can used as bit flags in the process of tree formatting.

   TFF_PLAIN_IDENTIFIER: unqualified part of a name.
   TFF_SCOPE: include the class and namespace scope of the name.
   TFF_CHASE_TYPEDEF: print the original type-id instead of the typedef-name.
   TFF_DECL_SPECIFIERS: print decl-specifiers.
   TFF_CLASS_KEY_OR_ENUM: precede a class-type name (resp. enum name) with
       a class-key (resp. `enum').
   TFF_RETURN_TYPE: include function return type.
   TFF_FUNCTION_DEFAULT_ARGUMENTS: include function default parameter values.
   TFF_EXCEPTION_SPECIFICATION: show function exception specification.
   TFF_TEMPLATE_HEADER: show the template<...> header in a
       template-declaration.
   TFF_TEMPLATE_NAME: show only template-name.
   TFF_EXPR_IN_PARENS: parenthesize expressions.
   TFF_NO_FUNCTION_ARGUMENTS: don't show function arguments.
   TFF_UNQUALIFIED_NAME: do not print the qualifying scope of the
       top-level entity.
   TFF_NO_OMIT_DEFAULT_TEMPLATE_ARGUMENTS: do not omit template arguments
       identical to their defaults.
   TFF_NO_TEMPLATE_BINDINGS: do not print information about the template
       arguments for a function template specialization.
   TFF_POINTER: we are printing a pointer type.  */

#define TFF_PLAIN_IDENTIFIER (0)
#define TFF_SCOPE (1)
#define TFF_CHASE_TYPEDEF (1 << 1)
#define TFF_DECL_SPECIFIERS (1 << 2)
#define TFF_CLASS_KEY_OR_ENUM (1 << 3)
#define TFF_RETURN_TYPE (1 << 4)
#define TFF_FUNCTION_DEFAULT_ARGUMENTS (1 << 5)
#define TFF_EXCEPTION_SPECIFICATION (1 << 6)
#define TFF_TEMPLATE_HEADER (1 << 7)
#define TFF_TEMPLATE_NAME (1 << 8)
#define TFF_EXPR_IN_PARENS (1 << 9)
#define TFF_NO_FUNCTION_ARGUMENTS (1 << 10)
#define TFF_UNQUALIFIED_NAME (1 << 11)
#define TFF_NO_OMIT_DEFAULT_TEMPLATE_ARGUMENTS (1 << 12)
#define TFF_NO_TEMPLATE_BINDINGS (1 << 13)
#define TFF_POINTER (1 << 14)

/* These constants can be used as bit flags to control strip_typedefs.

   STF_USER_VISIBLE: use heuristics to try to avoid stripping user-facing
       aliases of internal details.  This is intended for diagnostics,
       where it should (for example) give more useful "aka" types.

   STF_STRIP_DEPENDENT: allow the stripping of aliases with dependent
       template parameters, relying on code elsewhere to report any
       appropriate diagnostics.  */
const unsigned int STF_USER_VISIBLE = 1U;
const unsigned int STF_STRIP_DEPENDENT = 1U << 1;

/* Returns the TEMPLATE_DECL associated to a TEMPLATE_TEMPLATE_PARM
   node.  */
#define TEMPLATE_TEMPLATE_PARM_TEMPLATE_DECL(NODE)                             \
  ((TREE_CODE (NODE) == BOUND_TEMPLATE_TEMPLATE_PARM)                          \
     ? TYPE_TI_TEMPLATE (NODE)                                                 \
     : TYPE_NAME (NODE))

/* Given an ass_op_p boolean and a tree code, return a pointer to its
   overloaded operator info.  Tree codes for non-overloaded operators
   map to the error-operator.  */
#define OVL_OP_INFO(IS_ASS_P, TREE_CODE)                                       \
  (&ovl_op_info[(IS_ASS_P) != 0][ovl_op_mapping[(TREE_CODE)]])
/* Overloaded operator info for an identifier for which
   IDENTIFIER_OVL_OP_P is true.  */
#define IDENTIFIER_OVL_OP_INFO(NODE)                                           \
  (&ovl_op_info[IDENTIFIER_KIND_BIT_0 (NODE)][IDENTIFIER_CP_INDEX (NODE)])
#define IDENTIFIER_OVL_OP_FLAGS(NODE) (IDENTIFIER_OVL_OP_INFO (NODE)->flags)

#define assign_op_identifier (ovl_op_info[true][OVL_OP_NOP_EXPR].identifier)
#define call_op_identifier (ovl_op_info[false][OVL_OP_CALL_EXPR].identifier)

#define cp_walk_tree(tp, func, data, pset)                                     \
  walk_tree_1 (tp, func, data, pset, cp_walk_subtrees)
#define cp_walk_tree_without_duplicates(tp, func, data)                        \
  walk_tree_without_duplicates_1 (tp, func, data, cp_walk_subtrees)

// forked from gcc/c-family/c-common.h
/* Information about a statement tree.  */

struct GTY (()) stmt_tree_s
{
  /* A stack of statement lists being collected.  */
  vec<tree, va_gc> *x_cur_stmt_list;

  /* In C++, Nonzero if we should treat statements as full
     expressions.  In particular, this variable is non-zero if at the
     end of a statement we should destroy any temporaries created
     during that statement.  Similarly, if, at the end of a block, we
     should destroy any local variables in this block.  Normally, this
     variable is nonzero, since those are the normal semantics of
     C++.

     This flag has no effect in C.  */
  int stmts_are_full_exprs_p;
};

// forked from gcc/cp/namespace-lookup.h scope_kind
/* The kinds of scopes we recognize.  */
enum scope_kind
{
  sk_block = 0,	     /* An ordinary block scope.  This enumerator must
			have the value zero because "cp_binding_level"
			is initialized by using "memset" to set the
			contents to zero, and the default scope kind
			is "sk_block".  */
  sk_cleanup,	     /* A scope for (pseudo-)scope for cleanup.  It is
			pseudo in that it is transparent to name lookup
			activities.  */
  sk_try,	     /* A try-block.  */
  sk_catch,	     /* A catch-block.  */
  sk_for,	     /* The scope of the variable declared in a
			init-statement.  */
  sk_cond,	     /* The scope of the variable declared in the condition
			of an if or switch statement.  */
  sk_function_parms, /* The scope containing function parameters.  */
  sk_class,	     /* The scope containing the members of a class.  */
  sk_scoped_enum,    /* The scope containing the enumerators of a C++11
			scoped enumeration.  */
  sk_namespace,	     /* The scope containing the members of a
			namespace, including the global scope.  */
  sk_template_parms, /* A scope for template parameters.  */
  sk_template_spec,  /* Like sk_template_parms, but for an explicit
			specialization.  Since, by definition, an
			explicit specialization is introduced by
			"template <>", this scope is always empty.  */
  sk_transaction,    /* A synchronized or atomic statement.  */
  sk_omp	     /* An OpenMP structured block.  */
};

// forked from gcc/cp/namespace-lookup.h
/* The datatype used to implement C++ scope.  */
struct cp_binding_level;

// forked from gcc/cp/namepsace-lookup.h cxx_binding
/* Datatype that represents binding established by a declaration between
   a name and a C++ entity.  */
struct GTY (()) cxx_binding
{
  /* Link to chain together various bindings for this name.  */
  cxx_binding *previous;
  /* The non-type entity this name is bound to.  */
  tree value;
  /* The type entity this name is bound to.  */
  tree type;
  /* The scope at which this binding was made.  */
  cp_binding_level *scope;

  bool value_is_inherited : 1;
  bool is_local : 1;
  bool type_is_hidden : 1;
};

// forked from gcc/cp/namepsace-lookup.h cp_clas_binding
struct GTY (()) cp_class_binding
{
  cxx_binding *base;
  /* The bound name.  */
  tree identifier;
};

// forked from gcc/cp/namepsace-lookup.h cp_binding_level
/* For each binding contour we allocate a binding_level structure
   which records the names defined in that contour.
   Contours include:
    0) the global one
    1) one for each function definition,
       where internal declarations of the parameters appear.
    2) one for each compound statement,
       to record its declarations.

   The current meaning of a name can be found by searching the levels
   from the current one out to the global one.

   Off to the side, may be the class_binding_level.  This exists only
   to catch class-local declarations.  It is otherwise nonexistent.

   Also there may be binding levels that catch cleanups that must be
   run when exceptions occur.  Thus, to see whether a name is bound in
   the current scope, it is not enough to look in the
   CURRENT_BINDING_LEVEL.  You should use lookup_name_current_level
   instead.  */

struct GTY (()) cp_binding_level
{
  /* A chain of _DECL nodes for all variables, constants, functions,
      and typedef types.  These are in the reverse of the order
      supplied.  There may be OVERLOADs on this list, too, but they
      are wrapped in TREE_LISTs; the TREE_VALUE is the OVERLOAD.  */
  tree names;

  /* Using directives.  */
  vec<tree, va_gc> *using_directives;

  /* For the binding level corresponding to a class, the entities
      declared in the class or its base classes.  */
  vec<cp_class_binding, va_gc> *class_shadowed;

  /* Similar to class_shadowed, but for IDENTIFIER_TYPE_VALUE, and
      is used for all binding levels. The TREE_PURPOSE is the name of
      the entity, the TREE_TYPE is the associated type.  In addition
      the TREE_VALUE is the IDENTIFIER_TYPE_VALUE before we entered
      the class.  */
  tree type_shadowed;

  /* For each level (except not the global one),
      a chain of BLOCK nodes for all the levels
      that were entered and exited one level down.  */
  tree blocks;

  /* The entity (namespace, class, function) the scope of which this
      binding contour corresponds to.  Otherwise NULL.  */
  tree this_entity;

  /* The binding level which this one is contained in (inherits from).  */
  cp_binding_level *level_chain;

  /* STATEMENT_LIST for statements in this binding contour.
      Only used at present for SK_CLEANUP temporary bindings.  */
  tree statement_list;

  /* Binding depth at which this level began.  */
  int binding_depth;

  /* The kind of scope that this object represents.  However, a
      SK_TEMPLATE_SPEC scope is represented with KIND set to
      SK_TEMPLATE_PARMS and EXPLICIT_SPEC_P set to true.  */
  ENUM_BITFIELD (scope_kind) kind : 4;

  /* True if this scope is an SK_TEMPLATE_SPEC scope.  This field is
      only valid if KIND == SK_TEMPLATE_PARMS.  */
  BOOL_BITFIELD explicit_spec_p : 1;

  /* true means make a BLOCK for this level regardless of all else.  */
  unsigned keep : 1;

  /* Nonzero if this level can safely have additional
      cleanup-needing variables added to it.  */
  unsigned more_cleanups_ok : 1;
  unsigned have_cleanups : 1;

  /* Transient state set if this scope is of sk_class kind
     and is in the process of defining 'this_entity'.  Reset
     on leaving the class definition to allow for the scope
     to be subsequently re-used as a non-defining scope for
     'this_entity'.  */
  unsigned defining_class_p : 1;

  /* true for SK_FUNCTION_PARMS of immediate functions.  */
  unsigned immediate_fn_ctx_p : 1;

  /* 22 bits left to fill a 32-bit word.  */
};

// forked from gcc/cp/namespace-lookup.h cxx_saved_binding
/* Datatype used to temporarily save C++ bindings (for implicit
   instantiations purposes and like).  Implemented in decl.cc.  */
struct GTY (()) cxx_saved_binding
{
  /* The name of the current binding.  */
  tree identifier;
  /* The binding we're saving.  */
  cxx_binding *binding;
  tree real_type_value;
};

// forked from cp-tree.h omp_declare_target_attr
struct GTY (()) omp_declare_target_attr
{
  bool attr_syntax;
};

// forked from gcc/cp/cp-tree.h saved_scope
/* Global state.  */

struct GTY (()) saved_scope
{
  vec<cxx_saved_binding, va_gc> *old_bindings;
  tree old_namespace;
  vec<tree, va_gc> *decl_ns_list;
  tree class_name;
  tree class_type;
  tree access_specifier;
  tree function_decl;
  vec<tree, va_gc> *lang_base;
  tree lang_name;
  tree template_parms;
  cp_binding_level *x_previous_class_level;
  tree x_saved_tree;

  /* Only used for uses of this in trailing return type.  */
  tree x_current_class_ptr;
  tree x_current_class_ref;

  int x_processing_template_decl;
  int x_processing_specialization;
  int x_processing_constraint;
  int suppress_location_wrappers;
  BOOL_BITFIELD x_processing_explicit_instantiation : 1;
  BOOL_BITFIELD need_pop_function_context : 1;

  /* Nonzero if we are parsing the discarded statement of a constexpr
     if-statement.  */
  BOOL_BITFIELD discarded_stmt : 1;
  /* Nonzero if we are parsing or instantiating the compound-statement
     of consteval if statement.  Also set while processing an immediate
     invocation.  */
  BOOL_BITFIELD consteval_if_p : 1;

  int unevaluated_operand;
  int inhibit_evaluation_warnings;
  int noexcept_operand;
  int ref_temp_count;

  struct stmt_tree_s x_stmt_tree;

  cp_binding_level *class_bindings;
  cp_binding_level *bindings;

  hash_map<tree, tree> *GTY ((skip)) x_local_specializations;
  vec<omp_declare_target_attr, va_gc> *omp_declare_target_attribute;

  struct saved_scope *prev;
};

// forked from gcc/cp/cp-tree.h
extern GTY (()) struct saved_scope *scope_chain;

// forked from gcc/cp/cp-tree.h named_decl_hash
/* hash traits for declarations.  Hashes potential overload sets via
   DECL_NAME.  */

struct named_decl_hash : ggc_remove<tree>
{
  typedef tree value_type;   /* A DECL or OVERLOAD  */
  typedef tree compare_type; /* An identifier.  */

  inline static hashval_t hash (const value_type decl);
  inline static bool equal (const value_type existing, compare_type candidate);

  static const bool empty_zero_p = true;
  static inline void mark_empty (value_type &p) { p = NULL_TREE; }
  static inline bool is_empty (value_type p) { return !p; }

  /* Nothing is deletable.  Everything is insertable.  */
  static bool is_deleted (value_type) { return false; }
  static void mark_deleted (value_type) { gcc_unreachable (); }
};

// forked from gcc/cp/cp-tree.h tree_static_assert
struct GTY (()) tree_static_assert
{
  struct tree_common common;
  tree condition;
  tree message;
  location_t location;
};

// forked from gcc/cp/cp-tree.h cp_lambda_default_capture_mode_type
enum cp_lambda_default_capture_mode_type
{
  CPLD_NONE,
  CPLD_COPY,
  CPLD_REFERENCE
};

// forked from gcc/cp/cp-tree.h tree_lambda_expr
struct GTY (()) tree_lambda_expr
{
  struct tree_typed typed;
  tree capture_list;
  tree this_capture;
  tree extra_scope;
  tree regen_info;
  vec<tree, va_gc> *pending_proxies;
  location_t locus;
  enum cp_lambda_default_capture_mode_type default_capture_mode : 8;
  short int discriminator;
};

// forked from gcc/cp/cp-tree.h cp_trait_kind
/* The different kinds of traits that we encounter.  */

enum cp_trait_kind
{
  CPTK_BASES,
  CPTK_DIRECT_BASES,
  CPTK_HAS_NOTHROW_ASSIGN,
  CPTK_HAS_NOTHROW_CONSTRUCTOR,
  CPTK_HAS_NOTHROW_COPY,
  CPTK_HAS_TRIVIAL_ASSIGN,
  CPTK_HAS_TRIVIAL_CONSTRUCTOR,
  CPTK_HAS_TRIVIAL_COPY,
  CPTK_HAS_TRIVIAL_DESTRUCTOR,
  CPTK_HAS_UNIQUE_OBJ_REPRESENTATIONS,
  CPTK_HAS_VIRTUAL_DESTRUCTOR,
  CPTK_IS_ABSTRACT,
  CPTK_IS_AGGREGATE,
  CPTK_IS_BASE_OF,
  CPTK_IS_CLASS,
  CPTK_IS_EMPTY,
  CPTK_IS_ENUM,
  CPTK_IS_FINAL,
  CPTK_IS_LAYOUT_COMPATIBLE,
  CPTK_IS_LITERAL_TYPE,
  CPTK_IS_POINTER_INTERCONVERTIBLE_BASE_OF,
  CPTK_IS_POD,
  CPTK_IS_POLYMORPHIC,
  CPTK_IS_SAME_AS,
  CPTK_IS_STD_LAYOUT,
  CPTK_IS_TRIVIAL,
  CPTK_IS_TRIVIALLY_ASSIGNABLE,
  CPTK_IS_TRIVIALLY_CONSTRUCTIBLE,
  CPTK_IS_TRIVIALLY_COPYABLE,
  CPTK_IS_UNION,
  CPTK_UNDERLYING_TYPE,
  CPTK_IS_ASSIGNABLE,
  CPTK_IS_CONSTRUCTIBLE,
  CPTK_IS_NOTHROW_ASSIGNABLE,
  CPTK_IS_NOTHROW_CONSTRUCTIBLE
};

// forked from gcc/cp/cp-tree.h tree_trait_expr
struct GTY (()) tree_trait_expr
{
  struct tree_common common;
  tree type1;
  tree type2;
  location_t locus;
  enum cp_trait_kind kind;
};

// forked from gcc/cp/cp-tree.h tree_overload
/* OVL_HIDDEN_P nodes come before other nodes.  */

struct GTY (()) tree_overload
{
  struct tree_common common;
  tree function;
};

// forked from gcc/cp/cp-tree.h tree_baselink
struct GTY (()) tree_baselink
{
  struct tree_common common;
  tree binfo;
  tree functions;
  tree access_binfo;
};

// forked from gcc/cp/cp-tree.h deferred_access_check

/* The representation of a deferred access check.  */

struct GTY (()) deferred_access_check
{
  /* The base class in which the declaration is referenced. */
  tree binfo;
  /* The declaration whose access must be checked.  */
  tree decl;
  /* The declaration that should be used in the error message.  */
  tree diag_decl;
  /* The location of this access.  */
  location_t loc;
};

// forked from gcc/cp/cp-tree.h tree_template_info

struct GTY (()) tree_template_info
{
  struct tree_base base;
  tree tmpl;
  tree args;
  vec<deferred_access_check, va_gc> *deferred_access_checks;
};

// forked from gcc/cp/cp-tree.h lang_decl_selector

/* Discriminator values for lang_decl.  */

enum lang_decl_selector
{
  lds_min,
  lds_fn,
  lds_ns,
  lds_parm,
  lds_decomp
};

// forked from gcc/cp/cp-tree.h languages
enum languages
{
  lang_c,
  lang_cplusplus
};

// forked from gcc/cp/cp-tree.h lang_decl_base

/* Flags shared by all forms of DECL_LANG_SPECIFIC.

   Some of the flags live here only to make lang_decl_min/fn smaller.  Do
   not make this struct larger than 32 bits.  */

struct GTY (()) lang_decl_base
{
  ENUM_BITFIELD (lang_decl_selector) selector : 3;
  ENUM_BITFIELD (languages) language : 1;
  unsigned use_template : 2;
  unsigned not_really_extern : 1;    /* var or fn */
  unsigned initialized_in_class : 1; /* var or fn */

  unsigned threadprivate_or_deleted_p : 1; /* var or fn */
  /* anticipated_p is no longer used for anticipated_decls (fn, type
     or template).  It is used as DECL_OMP_PRIVATIZED_MEMBER in
     var.  */
  unsigned anticipated_p : 1;
  unsigned friend_or_tls : 1;	      /* var, fn, type or template */
  unsigned unknown_bound_p : 1;	      /* var */
  unsigned odr_used : 1;	      /* var or fn */
  unsigned concept_p : 1;	      /* applies to vars and functions */
  unsigned var_declared_inline_p : 1; /* var */
  unsigned dependent_init_p : 1;      /* var */

  /* The following apply to VAR, FUNCTION, TYPE, CONCEPT, & NAMESPACE
     decls.  */
  unsigned module_purview_p : 1; /* in module purview (not GMF) */
  unsigned module_import_p : 1;	 /* from an import */
  unsigned module_entity_p : 1;	 /* is in the entitity ary &
				    hash.  */
  /* VAR_DECL or FUNCTION_DECL has attached decls.     */
  unsigned module_attached_p : 1;

  /* 12 spare bits.  */
};

// forked from gcc/cp/cp-tree.h lang_decl_min

/* DECL_LANG_SPECIFIC for the above codes.  */

struct GTY (()) lang_decl_min
{
  struct lang_decl_base base; /* 32-bits.  */

  /* In a FUNCTION_DECL for which DECL_THUNK_P holds, this is
     THUNK_ALIAS.
     In a FUNCTION_DECL for which DECL_THUNK_P does not hold,
     VAR_DECL, TYPE_DECL, or TEMPLATE_DECL, this is
     DECL_TEMPLATE_INFO.  */
  tree template_info;

  /* In a DECL_THUNK_P FUNCTION_DECL, this is THUNK_VIRTUAL_OFFSET.
     In a lambda-capture proxy VAR_DECL, this is DECL_CAPTURED_VARIABLE.
     In a function-scope TREE_STATIC VAR_DECL or IMPLICIT_TYPEDEF_P TYPE_DECL,
     this is DECL_DISCRIMINATOR.
     In a DECL_LOCAL_DECL_P decl, this is the namespace decl it aliases.
     Otherwise, in a class-scope DECL, this is DECL_ACCESS.   */
  tree access;
};

// forked from gcc/cp/cp-tree.h lang_decl_fn
/* Additional DECL_LANG_SPECIFIC information for functions.  */

struct GTY (()) lang_decl_fn
{
  struct lang_decl_min min;

  /* In a overloaded operator, this is the compressed operator code.  */
  unsigned ovl_op_code : 6;
  unsigned global_ctor_p : 1;
  unsigned global_dtor_p : 1;

  unsigned static_function : 1;
  unsigned pure_virtual : 1;
  unsigned defaulted_p : 1;
  unsigned has_in_charge_parm_p : 1;
  unsigned has_vtt_parm_p : 1;
  unsigned pending_inline_p : 1;
  unsigned nonconverting : 1;
  unsigned thunk_p : 1;

  unsigned this_thunk_p : 1;
  unsigned omp_declare_reduction_p : 1;
  unsigned has_dependent_explicit_spec_p : 1;
  unsigned immediate_fn_p : 1;
  unsigned maybe_deleted : 1;
  unsigned coroutine_p : 1;
  unsigned implicit_constexpr : 1;

  unsigned spare : 9;

  /* 32-bits padding on 64-bit host.  */

  /* For a non-thunk function decl, this is a tree list of
     friendly classes. For a thunk function decl, it is the
     thunked to function decl.  */
  tree befriending_classes;

  /* For a virtual FUNCTION_DECL for which
     DECL_THIS_THUNK_P does not hold, this is DECL_THUNKS. Both
     this pointer and result pointer adjusting thunks are
     chained here.  This pointer thunks to return pointer thunks
     will be chained on the return pointer thunk.
     For a DECL_CONSTUCTOR_P FUNCTION_DECL, this is the base from
     whence we inherit.  Otherwise, it is the class in which a
     (namespace-scope) friend is defined (if any).   */
  tree context;

  union lang_decl_u5
  {
    /* In a non-thunk FUNCTION_DECL, this is DECL_CLONED_FUNCTION.  */
    tree GTY ((tag ("0"))) cloned_function;

    /* In a FUNCTION_DECL for which THUNK_P holds this is the
       THUNK_FIXED_OFFSET.  */
    HOST_WIDE_INT GTY ((tag ("1"))) fixed_offset;
  } GTY ((desc ("%1.thunk_p"))) u5;

  union lang_decl_u3
  {
    struct cp_token_cache *GTY ((tag ("1"))) pending_inline_info;
    tree GTY ((tag ("0"))) saved_auto_return_type;
  } GTY ((desc ("%1.pending_inline_p"))) u;
};

// forked from gcc/cp/cp-tree.h lang_decl_ns
/* DECL_LANG_SPECIFIC for namespaces.  */

struct GTY (()) lang_decl_ns
{
  struct lang_decl_base base; /* 32 bits.  */
  cp_binding_level *level;

  /* Inline children.  Needs to be va_gc, because of PCH.  */
  vec<tree, va_gc> *inlinees;

  /* Hash table of bound decls. It'd be nice to have this inline, but
     as the hash_map has a dtor, we can't then put this struct into a
     union (until moving to c++11).  */
  hash_table<named_decl_hash> *bindings;
};

// forked from gcc/cp/cp-tree.h lang_decl_parm
/* DECL_LANG_SPECIFIC for parameters.  */

struct GTY (()) lang_decl_parm
{
  struct lang_decl_base base; /* 32 bits.  */
  int level;
  int index;
};

// forked from gcc/cp/cp-tree.h lang_decl_decomp

/* Additional DECL_LANG_SPECIFIC information for structured bindings.  */

struct GTY (()) lang_decl_decomp
{
  struct lang_decl_min min;
  /* The artificial underlying "e" variable of the structured binding
     variable.  */
  tree base;
};

// forked from gcc/cp/cp-tree.h lang_decl

/* DECL_LANG_SPECIFIC for all types.  It would be nice to just make this a
   union rather than a struct containing a union as its only field, but
   tree.h declares it as a struct.  */

struct GTY (()) lang_decl
{
  union GTY ((desc ("%h.base.selector"))) lang_decl_u
  {
    /* Nothing of only the base type exists.  */
    struct lang_decl_base GTY ((default)) base;
    struct lang_decl_min GTY ((tag ("lds_min"))) min;
    struct lang_decl_fn GTY ((tag ("lds_fn"))) fn;
    struct lang_decl_ns GTY ((tag ("lds_ns"))) ns;
    struct lang_decl_parm GTY ((tag ("lds_parm"))) parm;
    struct lang_decl_decomp GTY ((tag ("lds_decomp"))) decomp;
  } u;
};

namespace Rust {

// forked from gcc/cp/cvt.cc convert_to_void
//
// When an expression is used in a void context, its value is discarded and
// no lvalue-rvalue and similar conversions happen [expr.static.cast/4,
// stmt.expr/1, expr.comma/1].  This permits dereferencing an incomplete type
// in a void context. The C++ standard does not define what an `access' to an
// object is, but there is reason to believe that it is the lvalue to rvalue
// conversion -- if it were not, `*&*p = 1' would violate [expr]/4 in that it
// accesses `*p' not to calculate the value to be stored. But, dcl.type.cv/8
// indicates that volatile semantics should be the same between C and C++
// where ever possible. C leaves it implementation defined as to what
// constitutes an access to a volatile. So, we interpret `*vp' as a read of
// the volatile object `vp' points to, unless that is an incomplete type. For
// volatile references we do not do this interpretation, because that would
// make it impossible to ignore the reference return value from functions. We
// issue warnings in the confusing cases.
//
// The IMPLICIT is ICV_CAST when the user is explicitly converting an
// expression to void via a cast. If an expression is being implicitly
// converted, IMPLICIT indicates the context of the implicit conversion.

/* Possible cases of implicit or explicit bad conversions to void. */
enum impl_conv_void
{
  ICV_CAST,	      /* (explicit) conversion to void */
  ICV_SECOND_OF_COND, /* second operand of conditional expression */
  ICV_THIRD_OF_COND,  /* third operand of conditional expression */
  ICV_RIGHT_OF_COMMA, /* right operand of comma operator */
  ICV_LEFT_OF_COMMA,  /* left operand of comma operator */
  ICV_STATEMENT,      /* statement */
  ICV_THIRD_IN_FOR    /* for increment expression */
};

extern tree
convert_to_void (tree expr, impl_conv_void implicit);

// The lvalue-to-rvalue conversion (7.1) is applied if and only if the
// expression is a glvalue of volatile-qualified type and it is one of the
// following:
// * ( expression ), where expression is one of these expressions,
// * id-expression (8.1.4),
// * subscripting (8.2.1),
// * class member access (8.2.5),
// * indirection (8.3.1),
// * pointer-to-member operation (8.5),
// * conditional expression (8.16) where both the second and the third
//   operands are one of these expressions, or
// * comma expression (8.19) where the right operand is one of these
//   expressions.
extern tree
mark_discarded_use (tree expr);

// Mark EXP as read, not just set, for set but not used -Wunused warning
// purposes.
extern void
mark_exp_read (tree exp);

// We've seen an actual use of EXPR.  Possibly replace an outer variable
// reference inside with its constant value or a lambda capture.
extern tree
mark_use (tree expr, bool rvalue_p, bool read_p, location_t loc,
	  bool reject_builtin);

// Called whenever the expression EXPR is used in an rvalue context.
// When REJECT_BUILTIN is true the expression is checked to make sure
// it doesn't make it possible to obtain the address of a GCC built-in
// function with no library fallback (or any of its bits, such as in
// a conversion to bool).
extern tree
mark_rvalue_use (tree e, location_t loc /* = UNKNOWN_LOCATION */,
		 bool reject_builtin /* = true */);

// Called whenever an expression is used in an lvalue context.
extern tree
mark_lvalue_use (tree expr);

// As above, but don't consider this use a read.
extern tree
mark_lvalue_use_nonread (tree expr);

// We are using a reference VAL for its value. Bash that reference all the way
// down to its lowest form.
extern tree
convert_from_reference (tree val);

// Subroutine of convert_to_void.  Warn if we're discarding something with
// attribute [[nodiscard]].
extern void
maybe_warn_nodiscard (tree expr, impl_conv_void implicit);

extern location_t
expr_loc_or_loc (const_tree t, location_t or_loc);

extern location_t
expr_loc_or_input_loc (const_tree t);

// FN is the callee of a CALL_EXPR or AGGR_INIT_EXPR; return the FUNCTION_DECL
// if we can.
extern tree
get_fndecl_from_callee (tree fn);

// FIXME some helpers from HIRCompileBase could probably be moved here over time

// Return an expression for the address of BASE[INDEX], used in offset intrinsic
extern tree
pointer_offset_expression (tree base_tree, tree index_tree, location_t locus);

// forked from gcc/cp/cp-tree.h template_info_decl_check
/* Returns t iff the node can have a TEMPLATE_INFO field.  */

inline tree
template_info_decl_check (const_tree t, const char *f, int l, const char *fn)
{
  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case FUNCTION_DECL:
    case FIELD_DECL:
    case TYPE_DECL:
    case CONCEPT_DECL:
    case TEMPLATE_DECL:
      return const_cast<tree> (t);
    default:
      break;
    }
  tree_check_failed (t, f, l, fn, VAR_DECL, FUNCTION_DECL, FIELD_DECL,
		     TYPE_DECL, CONCEPT_DECL, TEMPLATE_DECL, 0);
  gcc_unreachable ();
}

} // namespace Rust

#endif // RUST_TREE
