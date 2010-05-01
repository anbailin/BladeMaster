class DCMemStack
{
public:
	DCMemStack();
	DCMemStack(void* addr,uint32 size);

	void*		Alloc(uint32 size);
	void		Free(void* addr);
private:
	void*		mAddress;
	void*		mCurrent;
	uint32		mSize;

	std::vector<void*> mPendingFreeList;
};

DCMemStack::DCMemStack():
mAddress(NULL),mCurrent(NULL),mSize(0)
{
}


DCMemStack::DCMemStack(void *addr, uint32 size):
mAddress(addr),mCurrent(addr),mSize(size)
{

}
