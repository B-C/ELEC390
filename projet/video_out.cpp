#include "video_out.h"


void VIDEO_OUT::gen_images()
{
	image.pixel=new unsigned char[720*576];
	image.width=720;
	image.height=576;

	while(1)
	{
		if(!reset_n)
		{
		reset:
			current_image_number=0;
			wait();
		}
		else
		{
			while(!vref)
			{
				wait();
				if(reset_n == false)
					goto reset;
			}
			for(long i=0 ; i<image.height ; i++)
			{
				for(long j=0 ; j<image.width ; j++)
				{
					image.pixel[i*image.width+j]=pixel_in;

					wait();
					if(reset_n == false)
						goto reset;
				}

				while(!href)
				{
					wait();
					if(reset_n == false)
						goto reset;
				}
			}
			write_images();
		}
	}
}



// void VIDEO_OUT::zoom_image(long i, long j)
// {
// 	zoom.pixel[(2*i)*image.width+(2*j)]=
// 		zoom.pixel[(2*i+1)*image.width+(2*j)]=
// 		zoom.pixel[(2*i)*image.width+(2*j+1)]=
// 		zoom.pixel[(2*i+1)*image.width+(2*j+1)]=image.pixel[i*image.width+j];
// }

void VIDEO_OUT::write_images()
{
	char name[2048];

	sprintf(name, "%s%02d.png", base_name, current_image_number);
	image_write(&image,name);
	std::cerr<<"Ecriture de "<<name<<std::endl;

	current_image_number++;
}
