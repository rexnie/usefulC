int foo(void)
{
	return -1;
}

_start()
{
	foo();
	__asm__("leave");
}
