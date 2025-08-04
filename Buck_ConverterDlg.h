
// TiefsetzstellerDlg.h : header file
//

#pragma once
#include "graph.h"
#include "Model.h"
#include "AbstractController.h"
#include "ControllableObject.h"
#include "CVoltageController.h"
#include "CCircuit.h"
#include "CCapacitorController.h"
#include "CCoilController.h"
#include "CResistorController.h"
#include "CFrequencyController.h"
#include "CDutyCycleController.h"
#include "CSwitch.h"


// CTiefsetzstellerDlg dialog
class Buck_ConverterDlg : public CDialogEx
{
// Construction
public:
	Buck_ConverterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIEFSETZSTELLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CModel Model;
	// Graphs
	CGraph GraphTop;
	CGraph GraphMid;
	CGraph GraphBottom;
	
	// Views
	CCircuit Circuit;
	CSwitch Switch;
	// Controller 
	CAbstractController* AbstractController;
	
	CVoltageController VoltageController;
	CFrequencyController FrequencyController;

	CCapacitorController CapacitorController;
	CCoilController CoilController;
	CResistorController ResistorController;
	CDutyCycleController DutyCycleController;

	double EDIT_Inductance_Value;
	double EDIT_Capacity_Value;
	double EDIT_Resistor_Value;
	double EDIT_f0_Value;
	double EDIT_UD_Value;
	double EDIT_UControl_Value;
	double EDIT_D_Value;
	double EDIT_Ts_sz_Value;
	double EDIT_fs_sz_Value;
	

public:

	afx_msg void OnBnClickedOk();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEdit3();

	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit6();
};
