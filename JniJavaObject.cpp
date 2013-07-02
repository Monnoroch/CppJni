#include <JniJavaObject.h>
#include <JniJavaClass.h>


namespace JNI {

#ifdef MSYM_DEBUG_JNI_REF_CNT
int globalRefCnt = 0;
#endif


JavaClass JavaObject::GetClass() const {
	return JavaClass(_env, _env.Val()->GetObjectClass(Val()));
}

JavaObject JavaObject::New(const JavaClass& cls) {
	return cls.NewObject(); // JavaObject(cls._env, cls._env.Val()->AllocObject(cls.Val()));
}

JavaObject JavaObject::New(JavaEnv env, const std::string& cls) {
	return New(env.FindClass(cls));
}

}
