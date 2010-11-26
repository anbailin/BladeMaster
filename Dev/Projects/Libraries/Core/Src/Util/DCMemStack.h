class DCMemStack
{
public:
	DCMemStack();
	DCMemStack(void* addr,u32 size);

	void*		Alloc(u32 size);
	void		Free(void* addr);
private:
	void*		mAddress;
	void*		mCurrent;
	u32		mSize;

	std::vector<void*> mPendingFreeList;
};

DCMemStack::DCMemStack():
mAddress(NULL),mCurrent(NULL),mSize(0)
{
}


DCMemStack::DCMemStack(void *addr, u32 size):
mAddress(addr),mCurrent(addr),mSize(size)
{

}
