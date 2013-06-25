#ifndef MSYM_UTILS_JNI_JNI_FIELD_H
#define MSYM_UTILS_JNI_JNI_FIELD_H


#include <string>


#include <jni.h>


#include <JniHelper.h>
#include <JniClass.h>
#include <JniString.h>


namespace JNI
{
	struct JavaFieldHelper
	{
		template<class T>
		struct FieldGetter
		{
			T Get(JavaFieldHelper& self, jobject obj);
			void Set(JavaFieldHelper& self, jobject obj, T v);
		};

	public:
		JavaFieldHelper() : env(0), id(0) {}
		JavaFieldHelper(JNIEnv * e, jfieldID mid) : env(e), id(mid) {}
		JavaFieldHelper(const JavaFieldHelper& m) : env(m.env), id(m.id) {}

		bool Valid() const
		{
			return env != 0 && id != 0;
		}

		template<class T> T Get(jobject self)
		{
			return FieldGetter<T>().Get(*this, self);
		}

		template<class T> void Set(jobject self, T v)
		{
			return FieldGetter<T>().Set(*this, self, v);
		}

		virtual ~JavaFieldHelper() {}

		JNIEnv * env;
		jfieldID id;
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jboolean>
	{
		jboolean Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jboolean, &JNIEnv::GetBooleanField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jboolean v)
		{
			CallJniMethod<void, &JNIEnv::SetBooleanField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jbyte>
	{
		jbyte Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jbyte, &JNIEnv::GetByteField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jbyte v)
		{
			CallJniMethod<void, &JNIEnv::SetByteField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jchar>
	{
		jchar Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jchar, &JNIEnv::GetCharField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jchar v)
		{
			CallJniMethod<void, &JNIEnv::SetCharField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jshort>
	{
		jshort Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jshort, &JNIEnv::GetShortField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jshort v)
		{
			CallJniMethod<void, &JNIEnv::SetShortField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jint>
	{
		jint Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jint, &JNIEnv::GetIntField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jint v)
		{
			CallJniMethod<void, &JNIEnv::SetIntField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jlong>
	{
		jlong Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jlong, &JNIEnv::GetLongField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jlong v)
		{
			CallJniMethod<void, &JNIEnv::SetLongField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jfloat>
	{
		jfloat Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jfloat, &JNIEnv::GetFloatField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jfloat v)
		{
			CallJniMethod<void, &JNIEnv::SetFloatField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jdouble>
	{
		jdouble Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jdouble, &JNIEnv::GetDoubleField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jdouble v)
		{
			CallJniMethod<void, &JNIEnv::SetDoubleField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<jobject>
	{
		jobject Get(JavaFieldHelper& self, jobject obj)
		{
			return CallJniMethod<jobject, &JNIEnv::GetObjectField>(self.env, self.id, obj);
		}

		void Set(JavaFieldHelper& self, jobject obj, jobject v)
		{
			CallJniMethod<void, &JNIEnv::SetObjectField>(self.env, self.id, obj, v);
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<JavaObject>
	{
		JavaObject Get(JavaFieldHelper& self, jobject obj)
		{
			return JavaObject(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetObjectField>(self.env, self.id, obj));
		}

		void Set(JavaFieldHelper& self, jobject obj, const JavaObject& v)
		{
			CallJniMethod<void, &JNIEnv::SetObjectField>(self.env, self.id, obj, v.Val());
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<JavaString>
	{
		JavaString Get(JavaFieldHelper& self, jobject obj)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetObjectField>(self.env, self.id, obj));
		}

		void Set(JavaFieldHelper& self, jobject obj, const JavaString& v)
		{
			CallJniMethod<void, &JNIEnv::SetObjectField>(self.env, self.id, obj, v.Value());
		}
	};

	template<typename T>
	struct JavaFieldHelper::FieldGetter<JavaArray<T>>
	{
		JavaArray<T> Get(JavaFieldHelper& self, jobject obj)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::GetObjectField>(self.env, self.id, obj));
		}

		void Set(JavaFieldHelper& self, jobject obj, const JavaArray<T>& v)
		{
			CallJniMethod<void, &JNIEnv::SetObjectField>(self.env, self.id, obj, v.Value());
		}
	};

	template<>
	struct JavaFieldHelper::FieldGetter<std::string>
	{
		std::string Get(JavaFieldHelper& self, jobject obj)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetObjectField>(self.env, self.id, obj)).Value();
		}

		void Set(JavaFieldHelper& self, jobject obj, const std::string& v)
		{
			CallJniMethod<void, &JNIEnv::SetObjectField>(self.env, self.id, obj, v);
		}
	};

	struct JavaStaticFieldHelper : public JavaFieldHelper
	{
	private:

		template<class T>
		struct FieldGetter
		{
			T Get(JavaStaticFieldHelper& self, jobject obj);
			void Set(JavaStaticFieldHelper& self, jobject obj, T v);
		};

	public:
		JavaStaticFieldHelper(const JavaClass& c) : JavaFieldHelper(), cls(c) {}
		JavaStaticFieldHelper(const JavaClass& c, jfieldID mid) : JavaFieldHelper(c.Env(), mid), cls(c) {}
		JavaStaticFieldHelper(const JavaStaticFieldHelper& m) : JavaFieldHelper(m), cls(m.cls) {}

		bool Valid() const
		{
			return env != 0 && id != 0;
		}

		template<class T> T Get()
		{
			return FieldGetter<T>().Get(*this);
		}

		template<class T> void Set(T v)
		{
			return FieldGetter<T>().Set(*this, v);
		}

		virtual ~JavaStaticFieldHelper() {}

		JavaClass cls;
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jboolean>
	{
		jboolean Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jboolean, &JNIEnv::GetStaticBooleanField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jboolean v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticBooleanField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jbyte>
	{
		jbyte Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jbyte, &JNIEnv::GetStaticByteField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jbyte v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticByteField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jchar>
	{
		jchar Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jchar, &JNIEnv::GetStaticCharField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jchar v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticCharField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jshort>
	{
		jshort Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jshort, &JNIEnv::GetStaticShortField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jshort v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticShortField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jint>
	{
		jint Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jint, &JNIEnv::GetStaticIntField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jint v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticIntField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jlong>
	{
		jlong Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jlong, &JNIEnv::GetStaticLongField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jlong v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticLongField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jfloat>
	{
		jfloat Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jfloat, &JNIEnv::GetStaticFloatField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jfloat v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticFloatField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jdouble>
	{
		jdouble Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jdouble, &JNIEnv::GetStaticDoubleField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jdouble v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticDoubleField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<jobject>
	{
		jobject Get(JavaStaticFieldHelper& self)
		{
			return CallJniMethod<jobject, &JNIEnv::GetStaticObjectField>(self.env, self.id, self.cls.Val());
		}

		void Set(JavaStaticFieldHelper& self, jobject v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticObjectField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<JavaObject>
	{
		JavaObject Get(JavaStaticFieldHelper& self)
		{
			return JavaObject(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetStaticObjectField>(self.env, self.id, self.cls.Val()));
		}

		void Set(JavaStaticFieldHelper& self, const JavaObject& v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticObjectField>(self.env, self.id, self.cls.Val(), v.Val());
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<JavaString>
	{
		JavaString Get(JavaStaticFieldHelper& self)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetStaticObjectField>(self.env, self.id, self.cls.Val()));
		}

		void Set(JavaStaticFieldHelper& self, const JavaString& v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticObjectField>(self.env, self.id, self.cls.Val(), v.Value());
		}
	};

	template<typename T>
	struct JavaStaticFieldHelper::FieldGetter<JavaArray<T>>
	{
		JavaArray<T> Get(JavaStaticFieldHelper& self)
		{
			return JavaArray<T>(self.env, (jarray) CallJniMethod<jobject, &JNIEnv::GetStaticObjectField>(self.env, self.id, self.cls.Val()));
		}

		void Set(JavaStaticFieldHelper& self, const JavaArray<T>& v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticObjectField>(self.env, self.id, self.cls.Val(), v.Value());
		}
	};

	template<>
	struct JavaStaticFieldHelper::FieldGetter<std::string>
	{
		std::string Get(JavaStaticFieldHelper& self)
		{
			return JavaString(self.env, (jstring) CallJniMethod<jobject, &JNIEnv::GetStaticObjectField>(self.env, self.id, self.cls.Val())).Value();
		}

		void Set(JavaStaticFieldHelper& self, const std::string& v)
		{
			CallJniMethod<void, &JNIEnv::SetStaticObjectField>(self.env, self.id, self.cls.Val(), v);
		}
	};

	template<typename T>
	class JavaField : public JavaFieldHelper
	{
	public:
		JavaField() : JavaFieldHelper() {}
		JavaField(JNIEnv * e, jfieldID mid) : JavaFieldHelper(e, mid) {}
		JavaField(const JavaField& m) : JavaFieldHelper(m) {}

		T Get(jobject self)
		{
			return JavaFieldHelper::Get<T>(self);
		}

		void Set(jobject self, T v)
		{
			JavaFieldHelper::Set<T>(self, v);
		}
	};

	template<typename T>
	class JavaStaticField : public JavaStaticFieldHelper
	{
	public:
		JavaStaticField(const JavaClass& c) : JavaStaticFieldHelper(c) {}
		JavaStaticField(const JavaClass& c, jfieldID mid) : JavaStaticFieldHelper(c, mid) {}
		JavaStaticField(const JavaStaticField& m) : JavaStaticFieldHelper(m) {}

		T Get()
		{
			return JavaStaticFieldHelper::Get<T>();
		}

		void Set(T v)
		{
			JavaStaticFieldHelper::Set<T>(v);
		}
	};
}

#endif
