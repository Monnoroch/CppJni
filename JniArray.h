#ifndef MSYM_UTILS_JNI_JNI_ARRAY_H
#define MSYM_UTILS_JNI_JNI_ARRAY_H


#include <jni.h>


#include <JniObject.h>
#include <JniString.h>


namespace JNI
{

	/// Helper for receiving T[] from Java
	template<typename T>
	class JavaArray : public JavaObject
	{
		struct ArrayIniter
		{
			friend class JavaArray;
			void Init(const JavaArray<T>& self);
			void Deinit(const JavaArray<T>& self);
		};

		void Init()
		{
			if(Valid())
			{
				len = mEnv->GetArrayLength(Val());
				JavaArray<T>::ArrayIniter().Init(*this);
			}
		}

		void Deinit()
		{
			if(Valid())
				JavaArray<T>::ArrayIniter().Deinit(*this);
		}

	public:
		JavaArray() : JavaObject() {}
		JavaArray(JNIEnv * e, jarray a) : JavaObject(e, a)
		{
			JavaArray::Init();
		}

		JavaArray(const JavaArray& a) : JavaObject(a)
		{
			JavaArray::Init();
		}

		JavaArray(JavaArray&& a) : JavaObject(a)
		{
			T * tmp = ptr;
			ptr = a.ptr;
			a.ptr = tmp;

			jsize tmp1 = len;
			len = a.len;
			a.len = tmp1;
		}

		virtual ~JavaArray()
		{
			Deinit();
		}

		JavaArray& operator=(const JavaArray& a)
		{
			JavaArray::Deinit();
			Reset(a);
			JavaArray::Init();
			return *this;
		}

		const T& Get(jsize n) const
		{
			return ptr[n];
		}

		void Set(jsize n, T&& val)
		{
			ptr[n] = val;
		}

		T& operator[](jsize n)
		{
			return ptr[n];
		}

		const T& operator[](jsize n) const
		{
			return Get(n);
		}

		jsize Length() const { return len; }
		jarray Val() const { return (jarray) obj; }
		const T * Value() const { return ptr; }

		std::vector<T> ToVector() const
		{
			std::vector<T> res(len);
			res.assign(ptr, ptr + len);
			return res;
		}

		/// Data
	protected:
		T * ptr;
		jsize len;
	};


	template<>
	struct JavaArray<jboolean>::ArrayIniter
	{
		void Init(JavaArray<jboolean>& self)
		{
			self.ptr = self.mEnv->GetBooleanArrayElements((jbooleanArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jboolean>& self)
		{
			self.mEnv->ReleaseBooleanArrayElements((jbooleanArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jchar>::ArrayIniter
	{
		void Init(JavaArray<jchar>& self)
		{
			self.ptr = self.mEnv->GetCharArrayElements((jcharArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jchar>& self)
		{
			self.mEnv->ReleaseCharArrayElements((jcharArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jbyte>::ArrayIniter
	{
		void Init(JavaArray<jbyte>& self)
		{
			self.ptr = self.mEnv->GetByteArrayElements((jbyteArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jbyte>& self)
		{
			self.mEnv->ReleaseByteArrayElements((jbyteArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jshort>::ArrayIniter
	{
		void Init(JavaArray<jshort>& self)
		{
			self.ptr = self.mEnv->GetShortArrayElements((jshortArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jshort>& self)
		{
			self.mEnv->ReleaseShortArrayElements((jshortArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jint>::ArrayIniter
	{
		void Init(JavaArray<jint>& self)
		{
			self.ptr = self.mEnv->GetIntArrayElements((jintArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jint>& self)
		{
			self.mEnv->ReleaseIntArrayElements((jintArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jlong>::ArrayIniter
	{
		void Init(JavaArray<jlong>& self)
		{
			self.ptr = self.mEnv->GetLongArrayElements((jlongArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jlong>& self)
		{
			self.mEnv->ReleaseLongArrayElements((jlongArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jfloat>::ArrayIniter
	{
		void Init(JavaArray<jfloat>& self)
		{
			self.ptr = self.mEnv->GetFloatArrayElements((jfloatArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jfloat>& self)
		{
			self.mEnv->ReleaseFloatArrayElements((jfloatArray) self.Val(), self.ptr, 0);
		}
	};

	template<>
	struct JavaArray<jdouble>::ArrayIniter
	{
		void Init(JavaArray<jdouble>& self)
		{
			self.ptr = self.mEnv->GetDoubleArrayElements((jdoubleArray) self.Val(), NULL);
		}

		void Deinit(JavaArray<jdouble>& self)
		{
			self.mEnv->ReleaseDoubleArrayElements((jdoubleArray) self.Val(), self.ptr, 0);
		}
	};

	/// Helper for receiving Object[] from Java
	template<>
	class JavaArray<JavaObject> : public JavaObject
	{
		void Init()
		{
			if(Valid())
				len = mEnv->GetArrayLength(Val());
		}

	public:
		JavaArray() : JavaObject() {}
		JavaArray(JNIEnv * e, jarray a) : JavaObject(e, a)
		{
			JavaArray::Init();
		}

		JavaArray(const JavaArray& a) : JavaObject(a)
		{
			JavaArray::Init();
		}

		JavaArray(JavaArray&& a) : JavaObject(a)
		{
			jsize tmp = len;
			len = a.len;
			a.len = tmp;
		}

		virtual ~JavaArray() {}

		JavaArray& operator=(const JavaArray& a)
		{
			Reset(a);
			JavaArray::Init();
			return *this;
		}

		JavaObject Get(jsize n) const
		{
			return JavaObject(mEnv, mEnv->GetObjectArrayElement(Val(), n));
		}

		void Set(jsize n, const JavaObject& val)
		{
			mEnv->SetObjectArrayElement(Val(), n, val.Val());
		}

		JavaObject operator[](jsize n) const
		{
			return Get(n);
		}

		std::vector<JavaObject> ToVector() const
		{
			std::vector<JavaObject> res(len);
			for(jsize i = 0; i < len; ++i)
				res[i] = Get(i);
			return res;
		}

		jsize Length() const { return len; }
		jobjectArray Val() const { return (jobjectArray) obj; }

		/// Data
	protected:
		jsize len;
	};

	/// Helper for receiving Object[] from Java
	template<>
	class JavaArray<JavaString> : public JavaObject
	{
		void Init()
		{
			if(Valid())
				len = mEnv->GetArrayLength(Val());
		}

	public:
		JavaArray() : JavaObject() {}
		JavaArray(JNIEnv * e, jarray a) : JavaObject(e, a)
		{
			JavaArray::Init();
		}

		JavaArray(const JavaArray& a) : JavaObject(a)
		{
			JavaArray::Init();
		}

		JavaArray(JavaArray&& a) : JavaObject(a)
		{
			jsize tmp = len;
			len = a.len;
			a.len = tmp;
		}

		virtual ~JavaArray() {}

		JavaArray& operator=(const JavaArray& a)
		{
			Reset(a);
			JavaArray::Init();
			return *this;
		}

		JavaString Get(jsize n) const
		{
			return JavaString(mEnv, (jstring) mEnv->GetObjectArrayElement(Val(), n));
		}

		void Set(jsize n, const JavaString& val)
		{
			mEnv->SetObjectArrayElement(Val(), n, val.Val());
		}

		JavaString operator[](jsize n) const
		{
			return Get(n);
		}

		std::vector<JavaString> ToVector() const
		{
			std::vector<JavaString> res(len);
			for(jsize i = 0; i < len; ++i)
				res[i] = Get(i);
			return res;
		}

		jsize Length() const { return len; }
		jobjectArray Val() const { return (jobjectArray) obj; }

		/// Data
	protected:
		jsize len;
	};

	/// Helper for receiving Object[] from Java
	template<>
	class JavaArray<std::string> : public JavaObject
	{
		void Init()
		{
			if(Valid())
				len = mEnv->GetArrayLength(Val());
		}

	public:
		JavaArray() : JavaObject() {}
		JavaArray(JNIEnv * e, jarray a) : JavaObject(e, a)
		{
			JavaArray::Init();
		}

		JavaArray(const JavaArray& a) : JavaObject(a)
		{
			JavaArray::Init();
		}

		JavaArray(JavaArray&& a) : JavaObject(a)
		{
			jsize tmp = len;
			len = a.len;
			a.len = tmp;
		}

		virtual ~JavaArray() {}

		JavaArray& operator=(const JavaArray& a)
		{
			Reset(a);
			JavaArray::Init();
			return *this;
		}

		std::string Get(jsize n) const
		{
			return JavaString(mEnv, (jstring) mEnv->GetObjectArrayElement(Val(), n)).Value();
		}

		void Set(jsize n, const std::string& val)
		{
			// TODO: check if refcnt++ needed
			mEnv->SetObjectArrayElement(Val(), n, JavaString(mEnv, val.c_str()).Val());
		}

		std::string operator[](jsize n) const
		{
			return Get(n);
		}

		std::vector<std::string> ToVector() const
		{
			std::vector<std::string> res(len);
			for(jsize i = 0; i < len; ++i)
				res[i] = Get(i);
			return res;
		}

		jsize Length() const { return len; }
		jobjectArray Val() const { return (jobjectArray) obj; }

		/// Data
	protected:
		jsize len;
	};
}


#endif
