#include <JniHelper.h>
#include <JniJavaVM.h>


namespace JNI {

JniJavaVM * JniHelper::javaVmInstance = nullptr;

JniJavaVM& JniHelper::GetJavaVM() {
	if(javaVmInstance == nullptr)
		javaVmInstance = new JniJavaVM();
	return *javaVmInstance;
}

JniJavaVM& JniHelper::GetJavaVM(const std::string& classPath) {
	if(javaVmInstance == nullptr)
		javaVmInstance = new JniJavaVM(classPath);
	return *javaVmInstance;
}

JniJavaVM& JniHelper::GetJavaVM(const std::string& classPath, jint ver) {
	if(javaVmInstance == nullptr)
		javaVmInstance = new JniJavaVM(classPath, ver);
	return *javaVmInstance;
}



JniJavaVM& JniHelper::GetJavaVM(JavaVM * vm) {
	if(javaVmInstance == nullptr)
		javaVmInstance = new JniJavaVM(vm);
	return *javaVmInstance;
}

JniJavaVM& JniHelper::GetJavaVM(JavaVM * vm, jint ver) {
	if(javaVmInstance == nullptr)
		javaVmInstance = new JniJavaVM(vm, ver);
	return *javaVmInstance;
}

}
