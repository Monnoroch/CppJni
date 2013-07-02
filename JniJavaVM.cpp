#include <JniJavaVM.h>
#include <JniJavaEnv.h>


namespace JNI {

JavaEnv JniJavaVM::GetEnv() const {
	JNIEnv * env = nullptr;
	JavaVMAttachArgs attachArgs;

	jint res = val->GetEnv((void**) &env, Version());
	switch(res)
	{
		case JNI_OK:
			break;
		case JNI_EDETACHED:
			attachArgs.version = Version();
			attachArgs.name = (char*) "";
			attachArgs.group = 0;
			res = val->AttachCurrentThread((void**) &env, &attachArgs);
			if(res != JNI_OK)
			{
				printf("getJNIEnv: failed to attach to current thread.");
				return JavaEnv();
			}
			break;
		case JNI_EVERSION:
			printf("getJNIEnv: Unsupported JNI version.");
			return JavaEnv();
		default:
			printf("getJNIEnv: JNI API error.");
			return JavaEnv();
	}
	return JavaEnv(env);
}

}
