#ifndef MSYM_UTILS_JNI_JNI_STRING_H
#define MSYM_UTILS_JNI_JNI_STRING_H


#include <jni.h>


#include <JniObject.h>


namespace JNI
{

	/// Helper for receiving std::string from Java
	class JavaString : public JavaObject
	{
	private:
		void Init()
		{
			if(Valid())
				val = mEnv->GetStringUTFChars(Val(), 0);
		}

		void Destroy()
		{
			if(Valid())
				mEnv->ReleaseStringUTFChars(Val(), val);
		}

	public:
		JavaString() : JavaObject() {}
		JavaString(JNIEnv * e, const char * val) : JavaObject(e, e->NewStringUTF(val))
		{
			Init();
		}
		JavaString(JNIEnv * env, jstring str) : JavaObject(env, str)
		{
			Init();
		}
		JavaString(const JavaString& str) : JavaObject(str)
		{
			Init();
		}
		JavaString(JavaString&& str) : JavaObject(str)
		{
			const char * tmp = val;
			val = str.val;
			str.val = tmp;
		}

		virtual ~JavaString()
		{
			JavaString::Destroy();
		}

		JavaString& operator=(const JavaString& str)
		{
			Destroy();
			Reset(str);
			Init();
			return *this;
		}

		jstring Val() const { return (jstring) obj; }

		const char * Value() const
		{
			return val;
		}

		jsize Length() const
		{
			return mEnv->GetStringUTFLength(Val());
		}

	private:

		const char * val;
	};
}

#endif
