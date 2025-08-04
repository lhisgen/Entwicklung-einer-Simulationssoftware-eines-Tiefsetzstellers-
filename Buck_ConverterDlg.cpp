
// TiefsetzstellerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Buck_Converter.h"
#include "Buck_ConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTiefsetzstellerDlg dialog



Buck_ConverterDlg::Buck_ConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIEFSETZSTELLER_DIALOG, pParent)
	, GraphTop(0, 0, 0, 10, "GraphTop", &Model)
	, GraphMid(0, 0, -11, 11, "GraphMid", &Model)
	, GraphBottom(0, 0, -2, 2, "GraphBottom", &Model)
	, Circuit(&Model)
	, Switch(&Model)
	, FrequencyController(CPoint(0, 0), CPoint(0, 0), 15, 20, 120, 220, &Model, Model.getFrequency())
	, VoltageController(CPoint(0, 0), CPoint(0, 0), 15, 20, 120, 220, &Model, Model.getVoltage())
	, CapacitorController(CPoint(0, 0), CPoint(0, 0), 10, 36, 0, 0, &Model, Model.getCapacitor())
	, CoilController(CPoint(0, 0), CPoint(0, 0), 10, 36, 0, 0,&Model, Model.getCoil()) 
	, ResistorController(CPoint(0, 0), CPoint(0, 0), 36, 10, 0, 0, &Model, Model.getResistor())
	, DutyCycleController(CPoint(0, 0), CPoint(0, 0), 15, 20, 400, 800, &Model, Model.getDutyCycle())
	, EDIT_Inductance_Value(0.55)
	, EDIT_Capacity_Value(0.45)
	, EDIT_Resistor_Value(2.86)
	, EDIT_f0_Value(319.91)
	, EDIT_UD_Value(5.2)
	, EDIT_UControl_Value(2.808)
	, EDIT_D_Value(0.54)
	, EDIT_fs_sz_Value(1029.35)
	, EDIT_Ts_sz_Value(0.97)



{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
}

void Buck_ConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, EDIT_Inductance_Value);
	DDX_Text(pDX, IDC_EDIT3, EDIT_Capacity_Value);
	DDX_Text(pDX, IDC_EDIT4, EDIT_Resistor_Value);
	DDX_Text(pDX, IDC_EDIT5, EDIT_f0_Value);
	DDX_Text(pDX, IDC_EDIT6, EDIT_UD_Value);
	DDX_Text(pDX, IDC_EDIT7, EDIT_UControl_Value);
	DDX_Text(pDX, IDC_EDIT8, EDIT_D_Value);
	DDX_Text(pDX, IDC_EDIT9, EDIT_Ts_sz_Value);
	DDX_Text(pDX, IDC_EDIT10, EDIT_fs_sz_Value);
}

BEGIN_MESSAGE_MAP(Buck_ConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Buck_ConverterDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT3, &Buck_ConverterDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &Buck_ConverterDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT7, &Buck_ConverterDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &Buck_ConverterDlg::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_RADIO1, &Buck_ConverterDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &Buck_ConverterDlg::OnBnClickedRadio3)
	ON_EN_CHANGE(IDC_EDIT9, &Buck_ConverterDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT4, &Buck_ConverterDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT10, &Buck_ConverterDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT6, &Buck_ConverterDlg::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CTiefsetzstellerDlg message handlers

BOOL Buck_ConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CClientDC dc(this);

	// Anfangszustand des Model berechnen
	
	Invalidate();
	
	ModifyStyle(WS_THICKFRAME, 0); //Resizing ist damit nicht mehr möglich

	//Fenstergröße beim Start berechnen
	CRect RectStart;
	GetClientRect(&RectStart);
	int xWindowsSizeStart = RectStart.Width();
	int yWindowsSizeStart = RectStart.Height();

	Circuit.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	Circuit.CalcSizeOfView(xWindowsSizeStart, yWindowsSizeStart, &dc);
	Circuit.update(&dc);

	Switch.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	Switch.CalcSizeOfView(xWindowsSizeStart, yWindowsSizeStart, &dc);
	Switch.update(&dc);

	GraphTop.setXstartXorg(xWindowsSizeStart * 0.05);
	GraphTop.setYstartYorg((yWindowsSizeStart * 0.3333) - 3 * UPPER_MARGIN - yWindowsSizeStart * 0.2);
	GraphTop.update(&dc);

	GraphMid.setXstartXorg(xWindowsSizeStart * 0.05);
	GraphMid.setYstartYorg((yWindowsSizeStart * 0.6666) - 3 * UPPER_MARGIN - yWindowsSizeStart * 0.2);
	GraphMid.update(&dc);

	GraphBottom.setXstartXorg(xWindowsSizeStart * 0.05);
	GraphBottom.setYstartYorg((yWindowsSizeStart * 0.9999) - 3 * UPPER_MARGIN - yWindowsSizeStart * 0.2);
	GraphBottom.update(&dc);

	CoilController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	CoilController.CalcSizeOfViewStart(xWindowsSizeStart, yWindowsSizeStart, &dc);
	CoilController.setPositon(CPoint(xWindowsSizeStart * 0.75, yWindowsSizeStart / 8), CPoint(xWindowsSizeStart * 0.79, yWindowsSizeStart / 8), 10, yWindowsSizeStart / 19, xWindowsSizeStart * 0.75, xWindowsSizeStart * 0.832);

	CapacitorController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	CapacitorController.CalcSizeOfViewStart(xWindowsSizeStart, yWindowsSizeStart, &dc);
	CapacitorController.setPositon(CPoint(xWindowsSizeStart * 0.868, yWindowsSizeStart / 3.98), CPoint(xWindowsSizeStart * 0.89, yWindowsSizeStart / 3.98), xWindowsSizeStart*0.0085, yWindowsSizeStart / 15, xWindowsSizeStart * 0.882, xWindowsSizeStart * 0.915);

	ResistorController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	ResistorController.CalcSizeOfViewStart(xWindowsSizeStart, yWindowsSizeStart, &dc);
	ResistorController.setPositon(CPoint(xWindowsSizeStart * 0.946, yWindowsSizeStart * 0.185), CPoint(xWindowsSizeStart * 0.946, yWindowsSizeStart * 0.25), yWindowsSizeStart / 19, xWindowsSizeStart * 0.0088888889, yWindowsSizeStart * 0.192, yWindowsSizeStart * 0.304);
	
	VoltageController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	VoltageController.CalcSizeOfView(xWindowsSizeStart, yWindowsSizeStart, &dc);
	VoltageController.setPositon(CPoint(xWindowsSizeStart * 0.560888889, yWindowsSizeStart * 0.17857143), CPoint(xWindowsSizeStart * 0.560888889, yWindowsSizeStart * 0.25297619), xWindowsSizeStart * 0.0133333334, yWindowsSizeStart * 0.025, yWindowsSizeStart * 0.17857143, yWindowsSizeStart * 0.32738095);

	FrequencyController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	FrequencyController.CalcSizeOfViewStart(xWindowsSizeStart, yWindowsSizeStart, &dc);
	FrequencyController.setPositon(CPoint(xWindowsSizeStart * 0.61, yWindowsSizeStart * 0.185), CPoint(xWindowsSizeStart * 0.638, yWindowsSizeStart * 0.185), 10, yWindowsSizeStart / 38, xWindowsSizeStart * 0.61, xWindowsSizeStart * 0.67);

	DutyCycleController.setWindowSizeStart(xWindowsSizeStart, yWindowsSizeStart);
	DutyCycleController.CalcSizeOfView(xWindowsSizeStart, yWindowsSizeStart, &dc);
	DutyCycleController.setPositon(CPoint(xWindowsSizeStart * 0.61, yWindowsSizeStart * 0.215), CPoint(xWindowsSizeStart * 0.638, yWindowsSizeStart * 0.215), 10, yWindowsSizeStart / 38, xWindowsSizeStart * 0.61, xWindowsSizeStart * 0.67);

	double inductance_si = CoilController.calcInductance();
	EDIT_Inductance_Value = inductance_si * 1000; //output in mH
	double capacity_si = CapacitorController.calcCapacity();
	EDIT_Capacity_Value = capacity_si * 1000; //output in mF

	Model.setControllerValues(EDIT_Resistor_Value, capacity_si, inductance_si, EDIT_UD_Value, EDIT_fs_sz_Value, EDIT_D_Value);
	Model.SetParams(EDIT_Resistor_Value, inductance_si, capacity_si, EDIT_UD_Value, EDIT_D_Value, EDIT_fs_sz_Value);
	Model.calcModel(&dc);

	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
	CheckDlgButton(IDC_RADIO3, BST_UNCHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Buck_ConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to update the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Buck_ConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		
	}
	else
	{
		CPaintDC dc(this);
		CBrush backGrnd(RGB(255, 255, 255));  // Beispiel: Weißer Hintergrund
		dc.SelectObject(&backGrnd);	//Selbst gemacht, um zu Beginn einen weißen Hintergrund zu zeichnen.
		CRect rect;
		GetClientRect(&rect);
		dc.FillRect(&rect, &backGrnd);
		Model.calcModel(&dc);
		CDialogEx::OnPaint();
	
		
		
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Buck_ConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Buck_ConverterDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}




void Buck_ConverterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	// Lösche den vorhandenen Zeicheninhalt
		Invalidate();

	CPaintDC dc(this);
	CBrush backGrnd(RGB(255, 255, 255));  // Beispiel: Weißer Hintergrund
	dc.SelectObject(&backGrnd);	//Selbst gemacht, um zu Beginn einen weißen Hintergrund zu zeichnen.
	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, &backGrnd);

	 //Calculate the window width and height
	int xCurrentWindowSize = rect.Width();
	int yCurrentWindowSize = rect.Height();
	//Graph.update(&dc);
	
	Circuit.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	Circuit.update(&dc);

	Switch.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	Switch.update(&dc);

	CoilController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	CoilController.update(&dc);

	CapacitorController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	CapacitorController.update(&dc);

	ResistorController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	ResistorController.update(&dc);

	FrequencyController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	FrequencyController.update(&dc);

	DutyCycleController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	DutyCycleController.update(&dc);

	GraphTop.setXstartXorg(xCurrentWindowSize * 0.05);
	GraphTop.setYstartYorg((yCurrentWindowSize * 0.33333) - 3 * UPPER_MARGIN - yCurrentWindowSize * 0.2);
	GraphTop.setWidth(xCurrentWindowSize * 0.4);
	GraphTop.setHeight(yCurrentWindowSize * 0.2);
	GraphTop.update(&dc);

	GraphMid.setXstartXorg(xCurrentWindowSize * 0.05);
	GraphMid.setYstartYorg((yCurrentWindowSize * 0.6666) - 3 * UPPER_MARGIN - yCurrentWindowSize * 0.2);
	GraphMid.setWidth(xCurrentWindowSize * 0.4);
	GraphMid.setHeight(yCurrentWindowSize * 0.2);
	GraphMid.update(&dc);

	GraphBottom.setWidth(xCurrentWindowSize * 0.4);
	GraphBottom.setHeight(yCurrentWindowSize * 0.2);
	GraphBottom.setXstartXorg(xCurrentWindowSize * 0.05);
	GraphBottom.setYstartYorg((yCurrentWindowSize * 0.9999) - 3 * UPPER_MARGIN - yCurrentWindowSize * 0.2);
	GraphBottom.update(&dc);


	VoltageController.CalcSizeOfView(xCurrentWindowSize, yCurrentWindowSize, &dc);
	VoltageController.update(&dc);
	


	
}

//In dieser Funktion werden die Eigenschaften des Static Texts geändert
HBRUSH Buck_ConverterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkColor(RGB(255, 255, 255));
	
		//Hier für die Radio Buttons
		// Ändern Sie die Hintergrundfarbe des Gerätekontexts
		pDC->SetBkColor(RGB(255, 255, 255));

		// Erstellen Sie einen Pinsel mit der gewünschten Hintergrundfarbe
		HBRUSH hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

		// Rückgabe des neuen Pinsels
		return hbrBackground;
	// TODO:  Return a different brush if the default is not desired
	return hbr;
	
}



void Buck_ConverterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_LBUTTON) {
		CClientDC dc(this);
				if (AbstractController) {
					AbstractController->calcActualValue(point, &dc);
					AbstractController->update(&dc);
					double inductance_si = CoilController.calcInductance();
					EDIT_Inductance_Value = inductance_si *1000; //output in mH
					double capacity_si = CapacitorController.calcCapacity();
					EDIT_Capacity_Value = capacity_si *1000; //output in mF
					EDIT_Resistor_Value = ResistorController.calcResistance();
					EDIT_UD_Value = VoltageController.calcVoltage();
					EDIT_fs_sz_Value = FrequencyController.calcFrequency();
					EDIT_D_Value = DutyCycleController.calcDutyCycle();
					double u_control = EDIT_D_Value * EDIT_UD_Value;
					if (u_control * 100 - std::floor(u_control * 100) >= 0.5) {
						u_control = std::ceil(u_control * 100) / 100;
					}
					else {
						u_control = std::floor(u_control * 100) / 100;
					}
					EDIT_UControl_Value = u_control;
					double t_s = 1 / FrequencyController.calcFrequency() * 1000;
					if (t_s * 100 - std::floor(t_s * 100) >= 0.5) {
						t_s = std::ceil(t_s * 100) / 100;
					}
					else {
						t_s = std::floor(t_s * 100) / 100;
					}
					EDIT_Ts_sz_Value = t_s;
					double f0_round = sqrt(1 / (inductance_si * capacity_si)) / (2 * PI);
					if (f0_round * 100 - std::floor(f0_round * 100) >= 0.5) {
						f0_round = std::ceil(f0_round * 100) / 100;
					}
					else {
						f0_round = std::floor(f0_round * 100) / 100;
					}
					EDIT_f0_Value = f0_round;

					Model.setControllerValues(EDIT_Resistor_Value, capacity_si, inductance_si, EDIT_UD_Value, EDIT_fs_sz_Value, EDIT_D_Value);
					Model.SetParams(EDIT_Resistor_Value, inductance_si, capacity_si, EDIT_UD_Value, EDIT_D_Value, EDIT_fs_sz_Value);
					Model.calcModel(&dc);
					
				}
			}
			UpdateData(false);
		
	CDialogEx::OnMouseMove(nFlags, point);
}


void Buck_ConverterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	 //Überprüfen, welcher Controller ausgelöst hat.
	// Zeiger auf diesen Controller speichern
	// Wenn kein Controller ausgelöst hat, ist cPtr = NULL
	if (nFlags & MK_LBUTTON) {
		AbstractController = Model.getCtrPtr(point);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void Buck_ConverterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	// TODO: Add your message handler code here and/or call default
		if (AbstractController) {
		// bisher aktiven Conroller deaktivieren
		AbstractController = NULL;
		
	}
		
		
	CDialogEx::OnLButtonUp(nFlags, point);
}


void Buck_ConverterDlg::OnEnChangeEdit3()
{
	CClientDC dc(this);
	Model.calcModel(&dc);
	UpdateData(true);
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Buck_ConverterDlg::OnEnChangeEdit2() //Coil
{
	CClientDC dc(this);
	double inductance_si = CoilController.calcInductance();
	EDIT_Inductance_Value = inductance_si * 1000; //output in mH
	double capacity_si = CapacitorController.calcCapacity();
	EDIT_Capacity_Value = capacity_si * 1000; //output in mF
	EDIT_Resistor_Value = ResistorController.calcResistance();
	EDIT_UD_Value = VoltageController.calcVoltage();
	EDIT_fs_sz_Value = FrequencyController.calcFrequency();
	EDIT_D_Value = DutyCycleController.calcDutyCycle();
	double u_control = EDIT_D_Value * EDIT_UD_Value;
	if (u_control * 100 - std::floor(u_control * 100) >= 0.5) {
		u_control = std::ceil(u_control * 100) / 100;
	}
	else {
		u_control = std::floor(u_control * 100) / 100;
	}
	EDIT_UControl_Value = u_control;
	double t_s = 1 / FrequencyController.calcFrequency() * 1000;
	if (t_s * 100 - std::floor(t_s * 100) >= 0.5) {
		t_s = std::ceil(t_s * 100) / 100;
	}
	else {
		t_s = std::floor(t_s * 100) / 100;
	}
	EDIT_Ts_sz_Value = t_s;
	double f0_round = sqrt(1 / (inductance_si * capacity_si)) / (2 * PI);
	if (f0_round * 100 - std::floor(f0_round * 100) >= 0.5) {
		f0_round = std::ceil(f0_round * 100) / 100;
	}
	else {
		f0_round = std::floor(f0_round * 100) / 100;
	}
	EDIT_f0_Value = f0_round;

	Model.setControllerValues(EDIT_Resistor_Value, capacity_si, inductance_si, EDIT_UD_Value, EDIT_fs_sz_Value, EDIT_D_Value);
	Model.SetParams(EDIT_Resistor_Value, inductance_si, capacity_si, EDIT_UD_Value, EDIT_D_Value, EDIT_fs_sz_Value);
	Model.calcModel(&dc);
	UpdateData(true);
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Buck_ConverterDlg::OnEnChangeEdit7()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void Buck_ConverterDlg::OnEnChangeEdit8() //D_Value
{
	CClientDC dc(this);
	Model.calcModel(&dc);
	UpdateData(true);
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void Buck_ConverterDlg::OnBnClickedRadio1()
{
	CClientDC dc(this);
	Model.setSimulationStrategy();
	Model.calcModel(&dc);
	
}


void Buck_ConverterDlg::OnBnClickedRadio3()
{
	CClientDC dc(this);
	Model.setSimulationStrategy();
	Model.calcModel(&dc);
}


void Buck_ConverterDlg::OnEnChangeEdit9()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}



void Buck_ConverterDlg::OnEnChangeEdit4()
{
	CClientDC dc(this);
	Model.calcModel(&dc);
	UpdateData(true);
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void Buck_ConverterDlg::OnEnChangeEdit10()  //fsz_valaue
{
	CClientDC dc(this);
	Model.calcModel(&dc);
	UpdateData(true);
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void Buck_ConverterDlg::OnEnChangeEdit6() //ud
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}
