
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <config.h>
#include <encoding_manager.h>
#include <fonts_manager.h>
#include <disp_manager.h>
#include <input_manager.h>
#include <pic_operation.h>
#include <render.h>
#include <string.h>
#include <picfmt_manager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/* Useage��digitpic <freetype_file> */
int main(int argc, char **argv)
{	
	int iError;

	/* ��ʼ������ģ��: ����ͨ��"��׼���"Ҳ����ͨ��"����"��ӡ������Ϣ
	 * ��Ϊ�������Ͼ�Ҫ�õ�DBG_PRINTF����, �����ȳ�ʼ������ģ��
	 *
	 * ע�����ͨ�� 
	 */
	DebugInit();

	/* ��ʼ������ͨ�� */
	InitDebugChanel();

    /* ��ӡ�÷� */
	if (argc != 2) {
		DBG_PRINTF("Usage:\n");
		DBG_PRINTF("%s <freetype_file>\n", argv[0]);
		return 0;
	}
    
	/* ע����ʾ�豸 */
	DisplayInit();
    
	/* ���ܿ�֧�ֶ����ʾ�豸: ѡ��ͳ�ʼ��ָ������ʾ�豸 */
	SelectAndInitDefaultDispDev("fb");

	/* VideoMem: Ϊ�ӿ���ʾ�ٶ�,�����������ڴ��й������ʾ��ҳ�������,
	             (����ڴ��ΪVideoMem)
	 *           ��ʾʱ�ٰ�VideoMem�е����ݸ��Ƶ��豸���Դ���
	 * �����ĺ�����Ƿ���Ķ��ٸ�VideoMem
	 * ������ȡΪ0, ����ζ�����е���ʾ���ݶ�������ʾʱ���ֳ�����,Ȼ��д���Դ�
	 */
	AllocVideoMem(5);

    /* ע�������豸 
     * ����Ļ����ͱ�׼����
     */
	InputInit();
    
    /* �������������豸�ĳ�ʼ������ */
	AllInputDevicesInit();

    /* ע�����ģ�� */
    EncodingInit();

    /* ע���ֿ�ģ�� */
	iError = FontsInit();
	if (iError) {
		DBG_PRINTF("FontsInit error!\n");
	}
    
    /* ����freetype�ֿ����õ��ļ�������ߴ� */
	iError = SetFontsDetail("freetype", argv[1], 24);
	if (iError) {
		DBG_PRINTF("SetFontsDetail error!\n");
	}

    /* ע��ͼƬ�ļ�����ģ��
     * ��JPG��ʽ��BMP��ʽ
     */
    PicFmtsInit();

    /* ע��ҳ��
     * �����������ʹ�õ�6��ҳ��
     */
	PagesInit();

    /* ��������ҳ�� */
	Page("main")->Run(NULL);
		
	return 0;
}
