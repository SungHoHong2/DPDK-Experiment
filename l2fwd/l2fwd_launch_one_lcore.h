
/* main processing loop */
static void
l2fwd_main_loop(void)
{

  printf("hello");

}


static int
l2fwd_launch_one_lcore(__attribute__((unused)) void *dummy)
{
	l2fwd_main_loop();
	return 0;
}
