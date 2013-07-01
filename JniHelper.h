#ifndef MSYM_UTILS_JNI_JNI_HELPER_H
#define MSYM_UTILS_JNI_JNI_HELPER_H


#include <string>
#include <vector>


#include <jni.h>


#include <JniForwards.h>
#include <JniString.h>
#include <JniClass.h>


namespace JNI
{
	class JniHelper
	{
	public:
		JniHelper() : mJVM(nullptr) {}

		~JniHelper()
		{
			mJVM = nullptr;
		}

		jint Version() const
		{
			return JNI_VERSION_1_6;
		}

		jint Init(JavaVM * vm)
		{
			mJVM = vm;
			return Version();
		}

		JNIEnv * getJNIEnv() const
		{
			JNIEnv * env = nullptr;
			JavaVMAttachArgs attachArgs;

			jint res = mJVM->GetEnv((void**) &env, Version());
			switch(res)
			{
				case JNI_OK:
					break;
				case JNI_EDETACHED:
					attachArgs.version = Version();
					attachArgs.name = (char*) "";
					attachArgs.group = 0;
					res = mJVM->AttachCurrentThread((void**) &env, &attachArgs);
					if(res != JNI_OK)
					{
						// LOGE("getJNIEnv: failed to attach to current thread.");
						return nullptr;
					}
					break;
				case JNI_EVERSION:
					// LOGE("getJNIEnv: Unsupported JNI version.");
					return nullptr;
				default:
					// LOGE("getJNIEnv: JNI API error.");
					return nullptr;
			}
			return env;
		}

		static JniHelper * Instance()
		{
			static JniHelper instance;
			return &instance;
		}

	private:
		/// Data

		JavaVM * mJVM;
	};

	/*

	To add new type MyClass to JNI do the following:

	1) Create MyJavaWrapper inherited from JavaObject
	2) Create function:
	MyJavaWrapper JNI::MakeJniProxy(JNIEnv * e, const MyClass& v);
	3) Create
	template<>
	struct JNI::JavaMethodHelper::MethodCaller<MyClass>
	{
		template<typename ... Args>
		MyClass Call(JavaMethodHelper& self, Args...args);
	};
	and
	template<>
	struct JNI::JavaStaticMethodHelper::MethodCaller<MyClass>
	{
		template<typename ... Args>
		MyClass Call(JavaStaticMethodHelper& self, Args...args);
	};


	*/

	namespace _Helpers
	{
		template<typename T>
		struct JniCallProxy
		{
			JniCallProxy(T v) : val(v) {}
			T Val() const { return val; }
			T val;
		};
	}

	template<class T>
	static _Helpers::JniCallProxy<T> MakeJniProxy(JNIEnv * e, T v)
	{
		return _Helpers::JniCallProxy<T>(v);
	}

	static JavaString MakeJniProxy(JNIEnv * e, const char * v)
	{
		return JavaString(e, v);
	}

	static JavaString MakeJniProxy(JNIEnv * e, const std::string& v)
	{
		return JavaString(e, v.c_str());
	}

	/*

	jobject, jmethodID, ...
	jclass, jmethodID, ...

	jobject, jfieldID
	jclass, jfieldID

	*/

	template<typename R, R(JNIEnv::*f)(jobject, jmethodID, ...), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jmethodID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jmethodID, ...), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jmethodID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jmethodID, ...), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jmethodID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jmethodID, ...), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jmethodID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jboolean), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jboolean), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jboolean), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jboolean), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jchar), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jchar), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jchar), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jchar), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jbyte), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jbyte), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jbyte), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jbyte), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jshort), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jshort), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jshort), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jshort), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jint), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jint), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jint), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jint), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jlong), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jlong), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jlong), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jlong), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jfloat), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jfloat), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jfloat), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jfloat), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jdouble), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jdouble), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jdouble), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jdouble), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	///

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jobject), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jobject self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jobject, jfieldID, jobject), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaObject& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jobject), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, jclass self, Ts&&... vs)
	{
		return (env->*f)(self, id, MakeJniProxy(env, vs).Val()... );
	}

	template<typename R, R(JNIEnv::*f)(jclass, jfieldID, jobject), typename... Ts>
	static R CallJniMethod(JNIEnv *env, jfieldID id, const JavaClass& self, Ts&&... vs)
	{
		return CallJniMethod<R, f, Ts...>(env, id, self.Val(), vs...);
	}

}

#endif
