#if 0

#include <JniJavaClass.h>

int main()
{
    JNI::JavaClass c;
}

#elif 1

#include <JniJavaObject.h>
#include <JniJavaMethod.h>

int main()
{
    JNI::JavaObject o;
    o.GetMethod<int()>("");
}

#else

#include <JniJavaClass.h>
#include <JniJavaObject.h>
#include <JniJavaMethod.h>

int main()
{
    JNI::JavaClass c;
    JNI::JavaObject o;
    o.GetMethod<int()>("");
}

#endif
