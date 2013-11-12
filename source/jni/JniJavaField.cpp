#include <JniJavaField.h>


namespace JNI {

jboolean JavaFieldHelper<jboolean>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetBooleanField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jboolean>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetBooleanField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jchar JavaFieldHelper<jchar>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetCharField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jchar>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetCharField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jbyte JavaFieldHelper<jbyte>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetByteField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jbyte>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetByteField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jshort JavaFieldHelper<jshort>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetShortField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jshort>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetShortField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jint JavaFieldHelper<jint>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetIntField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jint>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetIntField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

// TestJniInt JavaFieldHelper<TestJniInt>::Get(const JavaField<T>& self) {
// 	return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetIntField(self.GetObject().Val(), self.Val())).Val();
// }
// void JavaFieldHelper<TestJniInt>::Set(const JavaField<T>& self, T&& val) {
// 	self.Env().Val()->SetIntField(self.GetObject().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
// }

jlong JavaFieldHelper<jlong>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetLongField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jlong>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetLongField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jfloat JavaFieldHelper<jfloat>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetFloatField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jfloat>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetFloatField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

jdouble JavaFieldHelper<jdouble>::Get(const JavaField<T>& self) {
	return self.Env().Val()->GetDoubleField(self.GetObject().Val(), self.Val());
}
void JavaFieldHelper<jdouble>::Set(const JavaField<T>& self, T&& val) {
	self.Env().Val()->SetDoubleField(self.GetObject().Val(), self.Val(), std::forward<T>(val));
}

/////////////////////////

jboolean JavaStaticFieldHelper<jboolean>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticBooleanField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jboolean>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticBooleanField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jchar JavaStaticFieldHelper<jchar>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticCharField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jchar>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticCharField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jbyte JavaStaticFieldHelper<jbyte>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticByteField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jbyte>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticByteField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jshort JavaStaticFieldHelper<jshort>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticShortField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jshort>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticShortField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jint JavaStaticFieldHelper<jint>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticIntField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jint>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticIntField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

// TestJniInt JavaStaticFieldHelper<TestJniInt>::Get(const JavaStaticField<T>& self) {
// 	return FromJavaProxy<T>(self.Env(), self.Env().Val()->GetStaticIntField(self.GetClass().Val(), self.Val())).Val();
// }
// void JavaStaticFieldHelper<TestJniInt>::Set(const JavaStaticField<T>& self, T&& val) {
// 	self.Env().Val()->SetStaticIntField(self.GetClass().Val(), self.Val(), ToJavaProxy<T>(self.Env(), std::forward<T>(val)).Val());
// }

jlong JavaStaticFieldHelper<jlong>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticLongField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jlong>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticLongField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jfloat JavaStaticFieldHelper<jfloat>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticFloatField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jfloat>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticFloatField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

jdouble JavaStaticFieldHelper<jdouble>::Get(const JavaStaticField<T>& self) {
	return self.Env().Val()->GetStaticDoubleField(self.GetClass().Val(), self.Val());
}
void JavaStaticFieldHelper<jdouble>::Set(const JavaStaticField<T>& self, T&& val) {
	self.Env().Val()->SetStaticDoubleField(self.GetClass().Val(), self.Val(), std::forward<T>(val));
}

}
