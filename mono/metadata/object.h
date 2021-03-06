#ifndef _MONO_CLI_OBJECT_H_
#define _MONO_CLI_OBJECT_H_

#include <mono/metadata/class.h>
#include <mono/utils/mono-error.h>

MONO_BEGIN_DECLS

typedef mono_byte MonoBoolean;

typedef struct _MonoString MonoString;
typedef struct _MonoArray MonoArray;
typedef struct _MonoReflectionMethod MonoReflectionMethod;
typedef struct _MonoReflectionAssembly MonoReflectionAssembly;
typedef struct _MonoReflectionModule MonoReflectionModule;
typedef struct _MonoReflectionField MonoReflectionField;
typedef struct _MonoReflectionProperty MonoReflectionProperty;
typedef struct _MonoReflectionEvent MonoReflectionEvent;
typedef struct _MonoReflectionType MonoReflectionType;
typedef struct _MonoDelegate MonoDelegate;
typedef struct _MonoException MonoException;
typedef struct _MonoThreadsSync MonoThreadsSync;
typedef struct _MonoThread MonoThread;
typedef struct _MonoDynamicAssembly MonoDynamicAssembly;
typedef struct _MonoDynamicImage MonoDynamicImage;
typedef struct _MonoReflectionMethodBody MonoReflectionMethodBody;
typedef struct _MonoAppContext MonoAppContext;

typedef struct {
	MonoVTable *vtable;
	MonoThreadsSync *synchronisation;
} MonoObject;

typedef MonoObject* (*MonoInvokeFunc)	     (MonoMethod *method, void *obj, void **params, MonoObject **exc);
typedef void*    (*MonoCompileFunc)	     (MonoMethod *method);
typedef void	    (*MonoMainThreadFunc)    (void* user_data);

#define MONO_OBJECT_SETREF(obj,fieldname,value) do {	\
		mono_gc_wbarrier_set_field ((MonoObject*)(obj), &((obj)->fieldname), (MonoObject*)value);	\
		/*(obj)->fieldname = (value);*/	\
	} while (0)

/* This should be used if 's' can reside on the heap */
#define MONO_STRUCT_SETREF(s,field,value) do { \
        mono_gc_wbarrier_generic_store (&((s)->field), (MonoObject*)(value)); \
    } while (0)

#define mono_array_addr(array,type,index) ((type*)(void*) mono_array_addr_with_size (array, sizeof (type), index))
#define mono_array_get(array,type,index) ( *(type*)mono_array_addr ((array), type, (index)) ) 
#define mono_array_set(array,type,index,value)	\
	do {	\
		type *__p = (type *) mono_array_addr ((array), type, (index));	\
		*__p = (value);	\
	} while (0)
#define mono_array_setref(array,index,value)	\
	do {	\
		void **__p = (void **) mono_array_addr ((array), void*, (index));	\
		mono_gc_wbarrier_set_arrayref ((array), __p, (MonoObject*)(value));	\
		/* *__p = (value);*/	\
	} while (0)
#define mono_array_memcpy_refs(dest,destidx,src,srcidx,count)	\
	do {	\
		void **__p = (void **) mono_array_addr ((dest), void*, (destidx));	\
		void **__s = mono_array_addr ((src), void*, (srcidx));	\
		mono_gc_wbarrier_arrayref_copy (__p, __s, (count));	\
	} while (0)

mono_unichar2 *mono_string_chars  (MonoString *s);
int            mono_string_length (MonoString *s);

MonoObject *
mono_object_new		    (MonoDomain *domain, MonoClass *klass);

MonoObject *
mono_object_new_specific    (MonoVTable *vtable);

/* can be used for classes without finalizer in non-profiling mode */
MonoObject *
mono_object_new_fast	    (MonoVTable *vtable);

MonoObject *
mono_object_new_alloc_specific (MonoVTable *vtable);

MonoObject *
mono_object_new_from_token  (MonoDomain *domain, MonoImage *image, uint32_t token);

MonoArray*
mono_array_new		    (MonoDomain *domain, MonoClass *eclass, uintptr_t n);

MonoArray*
mono_array_new_full	    (MonoDomain *domain, MonoClass *array_class,
			     uintptr_t *lengths, intptr_t *lower_bounds);

MonoArray *
mono_array_new_specific	    (MonoVTable *vtable, uintptr_t n);

MonoArray*
mono_array_clone	    (MonoArray *array);

char*
mono_array_addr_with_size   (MonoArray *array, int size, uintptr_t idx);

uintptr_t
mono_array_length           (MonoArray *array);

MonoString*
mono_string_new_utf16	    (MonoDomain *domain, const mono_unichar2 *text, int32_t len);

MonoString*
mono_string_new_size	    (MonoDomain *domain, int32_t len);

MonoString*
mono_ldstr		    (MonoDomain *domain, MonoImage *image, uint32_t str_index);

MonoString*
mono_string_is_interned	    (MonoString *str);

MonoString*
mono_string_intern	    (MonoString *str);

MonoString*
mono_string_new		    (MonoDomain *domain, const char *text);

MonoString*
mono_string_new_wrapper	    (const char *text);

MonoString*
mono_string_new_len	    (MonoDomain *domain, const char *text, unsigned int length);

char *
mono_string_to_utf8	    (MonoString *string_obj);

char *
mono_string_to_utf8_checked (MonoString *string_obj, MonoError *error);

mono_unichar2 *
mono_string_to_utf16	    (MonoString *string_obj);

MonoString *
mono_string_from_utf16	    (mono_unichar2 *data);

mono_bool
mono_string_equal           (MonoString *s1, MonoString *s2);

unsigned int
mono_string_hash            (MonoString *s);

int
mono_object_hash            (MonoObject* obj);

MonoString *
mono_object_to_string (MonoObject *obj, MonoObject **exc);

MonoObject *
mono_value_box		    (MonoDomain *domain, MonoClass *klass, void* val);

void
mono_value_copy             (void* dest, void* src, MonoClass *klass);

void
mono_value_copy_array       (MonoArray *dest, int dest_idx, void* src, int count);

MonoDomain*
mono_object_get_domain      (MonoObject *obj);

MonoClass*
mono_object_get_class       (MonoObject *obj);

void*
mono_object_unbox	    (MonoObject *obj);

MonoObject *
mono_object_clone	    (MonoObject *obj);

MonoObject *
mono_object_isinst	    (MonoObject *obj, MonoClass *klass);

MonoObject *
mono_object_isinst_mbyref   (MonoObject *obj, MonoClass *klass);

MonoObject *
mono_object_castclass_mbyref (MonoObject *obj, MonoClass *klass);

mono_bool 
mono_monitor_try_enter       (MonoObject *obj, uint32_t ms);

mono_bool
mono_monitor_enter           (MonoObject *obj);

unsigned int
mono_object_get_size         (MonoObject *o);

void 
mono_monitor_exit            (MonoObject *obj);

void
mono_raise_exception	    (MonoException *ex);

void
mono_runtime_object_init    (MonoObject *this_obj);

void
mono_runtime_class_init	    (MonoVTable *vtable);

MonoMethod*
mono_object_get_virtual_method (MonoObject *obj, MonoMethod *method);

MonoObject*
mono_runtime_invoke	    (MonoMethod *method, void *obj, void **params,
			     MonoObject **exc);

MonoMethod *
mono_get_delegate_invoke    (MonoClass *klass);

MonoObject*
mono_runtime_delegate_invoke (MonoObject *delegate, void **params, 
			      MonoObject **exc);

MonoObject*
mono_runtime_invoke_array   (MonoMethod *method, void *obj, MonoArray *params,
			     MonoObject **exc);

void*
mono_method_get_unmanaged_thunk (MonoMethod *method);

MonoArray*
mono_runtime_get_main_args  (void);

void
mono_runtime_exec_managed_code (MonoDomain *domain,
				MonoMainThreadFunc main_func,
				void* main_args);

int
mono_runtime_run_main	    (MonoMethod *method, int argc, char* argv[], 
			     MonoObject **exc);

int
mono_runtime_exec_main	    (MonoMethod *method, MonoArray *args,
			     MonoObject **exc);

void*
mono_load_remote_field (MonoObject *this_obj, MonoClass *klass, MonoClassField *field, void **res);

MonoObject *
mono_load_remote_field_new (MonoObject *this_obj, MonoClass *klass, MonoClassField *field);

void
mono_store_remote_field (MonoObject *this_obj, MonoClass *klass, MonoClassField *field, void* val);

void
mono_store_remote_field_new (MonoObject *this_obj, MonoClass *klass, MonoClassField *field, MonoObject *arg);

void
mono_unhandled_exception    (MonoObject *exc);

char*
mono_unhandled_exception_message (MonoObject *exc);

void
mono_print_unhandled_exception (MonoObject *exc);

void* 
mono_compile_method	   (MonoMethod *method);

/* accessors for fields and properties */
void
mono_field_set_value (MonoObject *obj, MonoClassField *field, void *value);

void
mono_field_static_set_value (MonoVTable *vt, MonoClassField *field, void *value);

void
mono_field_get_value (MonoObject *obj, MonoClassField *field, void *value);

void
mono_field_static_get_value (MonoVTable *vt, MonoClassField *field, void *value);

MonoObject *
mono_field_get_value_object (MonoDomain *domain, MonoClassField *field, MonoObject *obj);

void
mono_property_set_value (MonoProperty *prop, void *obj, void **params, MonoObject **exc);

MonoObject*
mono_property_get_value (MonoProperty *prop, void *obj, void **params, MonoObject **exc);

/* GC handles support 
 *
 * A handle can be created to refer to a managed object and either prevent it
 * from being garbage collected or moved or to be able to know if it has been 
 * collected or not (weak references).
 * mono_gchandle_new () is used to prevent an object from being garbage collected
 * until mono_gchandle_free() is called. Use a TRUE value for the pinned argument to
 * prevent the object from being moved (this should be avoided as much as possible 
 * and this should be used only for shorts periods of time or performance will suffer).
 * To create a weakref use mono_gchandle_new_weakref (): track_resurrection should
 * usually be false (see the GC docs for more details).
 * mono_gchandle_get_target () can be used to get the object referenced by both kinds
 * of handle: for a weakref handle, if an object has been collected, it will return NULL.
 */
uint32_t      mono_gchandle_new         (MonoObject *obj, mono_bool pinned);
uint32_t      mono_gchandle_new_weakref (MonoObject *obj, mono_bool track_resurrection);
MonoObject*  mono_gchandle_get_target  (uint32_t gchandle);
void         mono_gchandle_free        (uint32_t gchandle);

/* GC write barriers support */
void mono_gc_wbarrier_set_field     (MonoObject *obj, void* field_ptr, MonoObject* value);
void mono_gc_wbarrier_set_arrayref  (MonoArray *arr, void* slot_ptr, MonoObject* value);
void mono_gc_wbarrier_arrayref_copy (void* dest_ptr, void* src_ptr, int count);
void mono_gc_wbarrier_generic_store (void* ptr, MonoObject* value);
void mono_gc_wbarrier_generic_nostore (void* ptr);
void mono_gc_wbarrier_value_copy    (void* dest, void* src, int count, MonoClass *klass);
void mono_gc_wbarrier_object_copy   (MonoObject* obj, MonoObject *src);

MONO_END_DECLS

#endif

