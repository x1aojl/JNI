#include <iostream>
#include <jni.h>

int nativeFunc(JNIEnv* e, jobject o) {
    std::cout << "java call c++ native function" << std::endl;
    jfieldID fid = e->GetFieldID(e->GetObjectClass(o), "id", "I");
    return e->GetIntField(o, fid);
}

int main()
{
    JavaVM *jvm;
    JNIEnv *env;

    JavaVMInitArgs vm_args;

    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = "-Djava.class.path=.";
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;

    jclass cls = env->FindClass("Test");

    jmethodID mid = env->GetStaticMethodID(cls, "StaticFunc", "()V");
    env->CallStaticVoidMethod(cls, mid);

    JNINativeMethod methods[]{ { "NativeFunc", "()I", (int *)&nativeFunc } };
    env->RegisterNatives(cls, methods, 1);

    jmethodID ctor = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, ctor);
    jmethodID mid3 = env->GetMethodID(cls, "MemberFunc", "(I)I");
    jint result = env->CallIntMethod(obj, mid3, (jint)100);
    std::cout << "return " << result << std::endl;

    jvm->DestroyJavaVM();

    std::cin.get();
}
