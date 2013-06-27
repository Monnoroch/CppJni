#ifndef MSYM_UTILS_JNI_JNI_FORWARDS_H
#define MSYM_UTILS_JNI_JNI_FORWARDS_H


namespace JNI
{

	class JniHelper;

	class JavaObject;
	class JavaClass;
	class JavaString;

	template<typename T>
	class JavaArray;

	template<typename R>
	class JavaMethod;
	template<typename R>
	class JavaStaticMethod;

	template<typename T>
	class JavaField;
	template<typename T>
	class JavaStaticField;
}

#endif
