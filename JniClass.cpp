#include <JniClass.h>
#include <JniMethod.h>
#include <JniField.h>


namespace JNI
{

	jclass JavaClass::GetClass(JNIEnv * env, const char * name)
	{
		if(env == nullptr)
		{
			// LOGE("Cannot load class %s, broken JNIEnv.", name);
			return 0;
		}

		jclass cls = 0;
		bool dot = false;
		const char * tmp = name;
		while(*tmp != '\0')
		{
			if(*tmp == '.')
			{
				dot = true;
				break;
			}
			tmp++;
		}
		if(dot)
		{
			std::string s(name);
			for(size_t index = 0; index = s.find(".", index), index != std::string::npos;)
			{
				s.replace(index, 1, "/");
				index++;
			}
			cls = env->FindClass(s.c_str());
		}
		else cls = env->FindClass(name);

		// if(cls == 0)
		// 	LOGE("Cannot find class %s.", name);

		return cls;
	}

	JavaMethod<void> JavaClass::GetConstructor() const
	{
		return GetMethod<void>("<init>", "()V");
	}
}
