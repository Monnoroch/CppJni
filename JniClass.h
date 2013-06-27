#ifndef MSYM_UTILS_JNI_JNI_CLASS_H
#define MSYM_UTILS_JNI_JNI_CLASS_H

#include <jni.h>


#include <JniForwards.h>
#include <JniObject.h>


namespace JNI
{

	class JavaClass : public JavaObject
	{
	public:
		JavaClass() : JavaObject() {}
		JavaClass(JNIEnv * env, jclass c) : JavaObject(env, c) {}
		JavaClass(const JavaClass& c) : JavaObject(c) {}
		JavaClass(JavaClass&& c) : JavaObject(c) {}
		JavaClass(JNIEnv * env, const char * name) : JavaClass(env, GetClass(env, name)) {}

		virtual ~JavaClass() {}

		using JavaObject::operator=;

		jclass Val() const { return (jclass) obj; }

		template<typename R>
		JavaMethod<R> GetMethod(const char * name, const char * sig) const
		{
			jmethodID id = mEnv->GetMethodID(Val(), name, sig);
			if(id == 0)
			{
				// LOGE("JavaClass::GetMethod: cannot find method %s.", name);
				return JavaMethod<R>();
			}
			return JavaMethod<R>(mEnv, id);
		}

		template<typename R>
		JavaStaticMethod<R> GetStaticMethod(const char * name, const char * sig) const
		{
			jmethodID id = mEnv->GetStaticMethodID(Val(), name, sig);
			if(id == 0)
			{
				// LOGE("JavaClass::GetMethod: cannot find method %s.", name);
				return JavaStaticMethod<R>(*this);
			}
			return JavaStaticMethod<R>(*this, id);
		}
		JavaMethod<void> GetConstructor() const;

		template<typename T>
		JavaField<T> GetField(const char * name, const char * sig) const
		{
			jfieldID id = mEnv->GetFieldID(Val(), name, sig);
			if(id == 0)
			{
				// LOGE("JavaClass::GetField: cannot find method %s.", name);
				return JavaField<T>();
			}
			return JavaField<T>(mEnv, id);
		}

		template<typename T>
		JavaStaticField<T> GetStaticField(const char * name, const char * sig) const
		{
			jfieldID id = mEnv->GetStaticFieldID(Val(), name, sig);
			if(id == 0)
			{
				// LOGE("JavaClass::GetField: cannot find method %s.", name);
				return JavaStaticField<T>(*this);
			}
			return JavaStaticField<T>(*this, id);
		}

	private:

		static jclass GetClass(JNIEnv * env, const char * name);
	};
}

#endif
