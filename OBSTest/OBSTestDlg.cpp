
// OBSTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OBSTest.h"
#include "OBSTestDlg.h"
#include "afxdialogex.h"

#include "obs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COBSTestDlg �Ի���



COBSTestDlg::COBSTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COBSTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COBSTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	DDX_Control(pDX, IDC_COMBO_WINDOW, m_ComboWindow);
}

BEGIN_MESSAGE_MAP(COBSTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

void obs_enum_module_callback(void *param, obs_module_t *module)
{
	obs_module_t* pmodule = module;
}

bool obs_enum_sources_callback(void *param, obs_source_t* source)
{
	return true;
}

// COBSTestDlg ��Ϣ�������

BOOL COBSTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	bool result = obs_startup(nullptr, nullptr, nullptr);

	obs_load_all_modules();
	obs_log_loaded_modules();

	result = ResetAudio();

	result = ResetVideo();

	result = ResetOutputs();

	result = CreateWindowSource();

	result = CreateDisplayContext();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COBSTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COBSTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COBSTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool COBSTestDlg::ResetAudio()
{
	struct obs_audio_info ai;
	ai.samples_per_sec = 16000;
	ai.speakers = SPEAKERS_MONO;

	return obs_reset_audio(&ai);
}

bool COBSTestDlg::ResetVideo()
{
	struct obs_video_info ovi;
	ovi.graphics_module = "libobs-d3d11.dll";
	ovi.base_width = 1920;
	ovi.base_height = 1080;
	ovi.output_width = 1280;
	ovi.output_height = 720;
	ovi.output_format = VIDEO_FORMAT_NV12;
	ovi.colorspace = VIDEO_CS_601;
	ovi.range = VIDEO_RANGE_PARTIAL;
	ovi.adapter = 0;
	ovi.gpu_conversion = true;
	ovi.scale_type = OBS_SCALE_BICUBIC;

	return obs_reset_video(&ovi) == OBS_VIDEO_SUCCESS;
}

bool COBSTestDlg::ResetOutputs()
{
	h264Recording = obs_video_encoder_create("obs_x264", "simple_h264_stream", nullptr, nullptr);
	if (h264Recording)
		obs_encoder_release(h264Recording);
	
	aacRecording = obs_audio_encoder_create("CoreAudio_AAC", "simple_aac", nullptr, 0, nullptr);
	if (aacRecording)
		obs_encoder_release(aacRecording);

	fileOutput = obs_output_create("ffmpeg_muxer", "simple_file_output", nullptr, nullptr);
	if (fileOutput)
		obs_output_release(fileOutput);

	return h264Recording && aacRecording && fileOutput;
}

bool COBSTestDlg::CreateWindowSource()
{
	bool bRet = false;
	int id = 0;
	const char* type;
	while (obs_enum_input_types(id++, &type))
	{
		const char* name = obs_source_get_display_name(type);
		if (strcmp(name, "WindowCapture") == 0)
		{
			windowSource = obs_source_create(type, name, nullptr, nullptr);
			if (windowSource)
			{

				
				obs_properties_t* props = obs_source_properties(windowSource);
				obs_property_t* prop = obs_properties_first(props);
				while (prop)
				{
					const char* name = obs_property_name(prop);
					if (strcmp(name, "window") == 0)
					{
						int count = obs_property_list_item_count(prop);
						for (int i = 0; i < count; i++)
						{
							name = obs_property_list_item_name(prop, i);
							WCHAR name_u16[1024] = { 0 };
							::MultiByteToWideChar(CP_UTF8, 0, name, strlen(name), name_u16, 1024);
							m_ComboWindow.AddString(name_u16);
						}
						m_ComboWindow.SetCurSel(0);
						OBSData data = obs_source_get_settings(windowSource);
						obs_data_set_string(data, "window", obs_property_list_item_string(prop, 0));
						obs_data_item_t* item = obs_data_first(data);
						while (item)
						{
							name = obs_data_item_get_name(item);
							const char* content = obs_data_item_get_string(item);
							obs_data_item_next(&item);
							
						}
						//
						obs_source_update(windowSource, data);
						obs_source_inc_showing(windowSource);
						break;
					}

					obs_property_next(&prop);
				}
				obs_source_release(windowSource);
				bRet = true;
			}
		}
	}
	return bRet;
}

bool COBSTestDlg::CreateDisplayContext()
{
	CRect rectClient;
	m_StaticDisplay.GetClientRect(rectClient);
	gs_init_data info = {};
	info.cx = rectClient.Width();
	info.cy = rectClient.Height();
	info.format = GS_RGBA;
	info.zsformat = GS_ZS_NONE;
	info.window.hwnd = m_StaticDisplay.GetSafeHwnd();

	windowsDisplay = obs_display_create(&info);

	if (windowsDisplay)
		obs_display_add_draw_callback(windowsDisplay, COBSTestDlg::DrawMain, this);

	return windowsDisplay != nullptr;
}

void COBSTestDlg::DrawMain(void* data, uint32_t cx, uint32_t cy)
{
	if (!data)
		return;

	COBSTestDlg* pDlg = (COBSTestDlg*)data;
	uint32_t sourceCX = obs_source_get_width(pDlg->windowSource);
	uint32_t sourceCY = obs_source_get_height(pDlg->windowSource);

	gs_viewport_push();
	gs_projection_push();
	gs_ortho(0.0f, float(sourceCX), 0.0f, float(sourceCY),
		-100.0f, 100.0f);
	gs_set_viewport(0, 0, cx, cy);
	
	obs_source_video_render(pDlg->windowSource);

	gs_projection_pop();
	gs_viewport_pop();
}

