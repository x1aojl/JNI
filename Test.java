public class Test {
	private int id;

	public Test() {
        System.out.println("c++ new java object");
    }

	public static void StaticFunc() {
		System.out.println("c++ call java static function");
	}
	
    public int MemberFunc(int id) {
		this.id = id;
        System.out.println("c++ call java member function");
		return NativeFunc();
    }
	
	public native int NativeFunc();
}