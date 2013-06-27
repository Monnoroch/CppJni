#ifndef MSYM_UTILS_JNI_JNI_OBJECT_H
#define MSYM_UTILS_JNI_JNI_OBJECT_H

#include <jni.h>


#include <JniForwards.h>


namespace JNI
{
	// static int global_ref_cnst = 0; // DEBUG

	/// Базовый класс для проксирования джавовых обьектов
	/// Все прокси наследовать от него!
	class JavaObject
	{
		struct JavaObjectHelper
		{
			JNIEnv * mEnv;
			jobject obj;
		};

	public:
		JavaObject() : mEnv(0), obj(0) {}
		JavaObject(JNIEnv * env, jobject o) : mEnv(env), obj(o)
		{
			// global_ref_cnt++; // DEBUG
		}
		JavaObject(const JavaObjectHelper& helper) : JavaObject(helper.mEnv, helper.obj) {}
		JavaObject(const JavaObject& o)
		{
			Init(o);
		}
		JavaObject(JavaObject&& o)
		{
			JNIEnv * tmp = mEnv;
			mEnv = o.mEnv;
			o.mEnv = tmp;

			jobject tmp1 = obj;
			obj = o.obj;
			o.obj = tmp1;
		}

		JavaObject& operator=(const JavaObject& o)
		{
			Reset(o);
			return *this;
		}

		virtual ~JavaObject()
		{
			Destroy();
		}

		bool Valid() const { return mEnv != 0; }
		JNIEnv * Env() const { return mEnv; }

		/// Нужно имплементировать!
		jobject Val() const { return obj; }

	protected:
		void Reset(const JavaObject& o)
		{
			Destroy();
			Init(o);
		}

	private:
		void Init(const JavaObject& o)
		{
			mEnv = o.mEnv;
			if(o.Valid())
			{
				obj = mEnv->NewLocalRef(o.obj);
				// global_ref_cnt++; // DEBUG
			}
		}

		void Destroy()
		{
			if(Valid())
			{
				// global_ref_cnt--; // DEBUG
				mEnv->DeleteLocalRef(obj);
			}
		}

	protected:
		JNIEnv * mEnv;
		jobject obj;
	};
}

#endif
