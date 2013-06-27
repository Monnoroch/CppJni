#ifndef MSYM_UTILS_JNI_JNI_METHOD_H
#define MSYM_UTILS_JNI_JNI_METHOD_H


#include <string>


#include <jni.h>


#include <JniForwards.h>
#include <JniHelper.h>
#include <JniClass.h>
#include <JniString.h>
#include <JniArray.h>


namespace JNI
{
	struct JavaMethodHelper
	{
		template<class T>
		struct MethodCaller
		{
			template<typename ... Args> T Call(JavaMethodHelper& self, Args...args);
		};

	public:
		JavaMethodHelper() : env(0), id(0) {}
		JavaMethodHelper(JNIEnv * e, jmethodID mid) : env(e), id(mid) {}
		JavaMethodHelper(const JavaMethodHelper& m) : env(m.env), id(m.id) {}

		bool Valid() const
		{
			return env != 0 && id != 0;
		}

		template<class T, typename ... Args> T Call(Args...args)
		{
			return MethodCaller<T>().Call(*this, args...);
		}

		virtual ~JavaMethodHelper() {}

		JNIEnv * env;
		jmethodID id;
	};

	template<>
	struct JavaMethodHelper::MethodCaller<void>
	{
		template<typename ... Args>
		void Call(JavaMethodHelper& self, Args...args)
		{
			CallJniMethod<void, &JNIEnv::CallVoidMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jboolean>
	{
		template<typename ... Args>
		jboolean Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jboolean, &JNIEnv::CallBooleanMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jchar>
	{
		template<typename ... Args>
		jchar Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jchar, &JNIEnv::CallCharMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jbyte>
	{
		template<typename ... Args>
		jbyte Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jbyte, &JNIEnv::CallByteMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jshort>
	{
		template<typename ... Args>
		jshort Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jshort, &JNIEnv::CallShortMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jint>
	{
		template<typename ... Args>
		jint Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jint, &JNIEnv::CallIntMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jlong>
	{
		template<typename ... Args>
		jlong Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jlong, &JNIEnv::CallLongMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jfloat>
	{
		template<typename ... Args>
		jfloat Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jfloat, &JNIEnv::CallFloatMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jdouble>
	{
		template<typename ... Args>
		jdouble Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jdouble, &JNIEnv::CallDoubleMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<jobject>
	{
		template<typename ... Args>
		jobject Call(JavaMethodHelper& self, Args...args)
		{
			return CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...);
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<JavaObject>
	{
		template<typename ... Args>
		JavaObject Call(JavaMethodHelper& self, Args...args)
		{
			return JavaObject(self.env, CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...));
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<JavaString>
	{
		template<typename ... Args>
		JavaString Call(JavaMethodHelper& self, Args...args)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...));
		}
	};

	template<typename T>
	struct JavaMethodHelper::MethodCaller<JavaArray<T>>
	{
		template<typename ... Args>
		JavaArray<T> Call(JavaMethodHelper& self, Args...args)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...));
		}
	};

	template<>
	struct JavaMethodHelper::MethodCaller<std::string>
	{
		template<typename ... Args>
		std::string Call(JavaMethodHelper& self, Args...args)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...)).Value();
		}
	};

	template<typename T>
	struct JavaMethodHelper::MethodCaller<std::vector<T>>
	{
		template<typename ... Args>
		std::vector<T> Call(JavaMethodHelper& self, Args...args)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::CallObjectMethod>(self.env, self.id, args...)).ToVector();
		}
	};

	struct JavaStaticMethodHelper : public JavaMethodHelper
	{
		template<class T>
		struct MethodCaller
		{
			template<typename ... Args> T Call(Args...args) {}
		};

	public:
		JavaStaticMethodHelper(const JavaClass& c) : JavaMethodHelper(), cls(c) {}
		JavaStaticMethodHelper(const JavaClass& c, jmethodID mid) : JavaMethodHelper(c.Env(), mid), cls(c) {}
		JavaStaticMethodHelper(const JavaStaticMethodHelper& m) : JavaMethodHelper(m), cls(m.cls) {}

		template<class T, typename ... Args> T Call(Args...args)
		{
			return JavaStaticMethodHelper::MethodCaller<T>().Call(*this, args...);
		}

		JavaClass cls;
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<void>
	{
		template<typename ... Args>
		void Call(JavaStaticMethodHelper& self, Args...args)
		{
			CallJniMethod<void, &JNIEnv::CallStaticVoidMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jboolean>
	{
		template<typename ... Args>
		jboolean Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jboolean, &JNIEnv::CallStaticBooleanMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jchar>
	{
		template<typename ... Args>
		jchar Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jchar, &JNIEnv::CallStaticCharMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jbyte>
	{
		template<typename ... Args>
		jbyte Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jbyte, &JNIEnv::CallStaticByteMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jshort>
	{
		template<typename ... Args>
		jshort Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jshort, &JNIEnv::CallStaticShortMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jint>
	{
		template<typename ... Args>
		jint Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jint, &JNIEnv::CallStaticIntMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jlong>
	{
		template<typename ... Args>
		jlong Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jlong, &JNIEnv::CallStaticLongMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jfloat>
	{
		template<typename ... Args>
		jfloat Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jfloat, &JNIEnv::CallStaticFloatMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jdouble>
	{
		template<typename ... Args>
		jdouble Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jdouble, &JNIEnv::CallStaticDoubleMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<jobject>
	{
		template<typename ... Args>
		jobject Call(JavaStaticMethodHelper& self, Args...args)
		{
			return CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...);
		}
	};
	
	template<>
	struct JavaStaticMethodHelper::MethodCaller<JavaObject>
	{
		template<typename ... Args>
		JavaObject Call(JavaStaticMethodHelper& self, Args...args)
		{
			return JavaObject(self.env, CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...));
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<JavaString>
	{
		template<typename ... Args>
		JavaString Call(JavaStaticMethodHelper& self, Args...args)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...));
		}
	};

	template<typename T>
	struct JavaStaticMethodHelper::MethodCaller<JavaArray<T>>
	{
		template<typename ... Args>
		JavaArray<T> Call(JavaStaticMethodHelper& self, Args...args)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...));
		}
	};

	template<>
	struct JavaStaticMethodHelper::MethodCaller<std::string>
	{
		template<typename ... Args>
		std::string Call(JavaStaticMethodHelper& self, Args...args)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...)).Value();
		}
	};

	template<typename T>
	struct JavaStaticMethodHelper::MethodCaller<std::vector<T>>
	{
		template<typename ... Args>
		std::vector<T> Call(JavaStaticMethodHelper& self, Args...args)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::CallStaticObjectMethod>(self.env, self.id, self.cls.Val(), args...)).ToVector();
		}
	};


	template<typename R>
	class JavaMethod : public JavaMethodHelper
	{
	public:
		JavaMethod() : JavaMethodHelper() {}
		JavaMethod(JNIEnv * e, jmethodID mid) : JavaMethodHelper(e, mid) {}
		JavaMethod(const JavaMethod& m) : JavaMethodHelper(m) {}

		template<typename ... Args>
		R operator()(Args ... args)
		{
			return Call<R, Args...>(args...);
		}
	};

	template<typename R>
	class JavaStaticMethod : public JavaStaticMethodHelper
	{
	public:
		JavaStaticMethod(const JavaClass& c) : JavaStaticMethodHelper(c) {}
		JavaStaticMethod(const JavaClass& c, jmethodID mid) : JavaStaticMethodHelper(c, mid) {}
		JavaStaticMethod(const JavaStaticMethod& m) : JavaStaticMethodHelper(m) {}

		template<typename ... Args>
		R operator()(Args ... args)
		{
			return Call<R, Args...>(args...);
		}
	};
}

#endif
