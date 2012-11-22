#ifndef RINGBUF_H_INC
#define RINGBUF_H_INC


template<class T, long bufSize>
class ringbuffer
{
	protected:
		T buf[bufSize];
		long read, write;
	public:
		ringbuffer()
		{
			read=0; write=1;
		}
		bool operator << (T &obj)
		{
			buf[write]=obj;
			++write;
			while(write>=bufSize)write-=bufSize;
			if(write==read)
			{
				--write; //make sure this happens next time
				while(write<0)write+=bufSize;
				return false;
			}
			return true;
		}
		bool operator >> (T &res)
		{
			++read;
			while(read>=bufSize)read-=bufSize;
			if(read==write)
			{
				++write; //make sure this happens next time we call and the buf is still empty
				while(write>=bufSize)write-=bufSize;
				return false;
			}
			res=buf[read];
			return true;
		}
		unsigned long dataSize()
		{
			unsigned long wc=write;
			while(wc<read)wc+=bufSize;
			return wc-read-1;
		}
		void flood(const T &value)
		{
			//loop through all indices, flooding them
			//this is basically a reset
			read=0;
			for(write=0;write<bufSize;write++)
			{
				buf[write]=value;
			}
			write=1;
		}
};


#endif