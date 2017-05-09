#define QUE_SIZE 100
struct mtable
{
	u32 time_sec[QUE_SIZE];
	u32 time_us[QUE_SIZE];
	u8 v[QUE_SIZE];
	u8 head;
	u8 tail;
	u8 ov;//¶ÓÁÐÒç³ö
}
void que_init(void)
{
	head = 0;
	tail = 0;
	ov = 0;
}

void que_insert(u32 sec, u32 us, u8 v)
{
	u8 ptr;
	ptr = (tail + 1) % QUE_SIZE;
	if (ptr == head)
	{
		ov = 1;
	}
	else
	{
		tail = ptr;
		time_sec[tail] = sec;
		time_us[tail] = us;
		v[tail] = v;
	}
}