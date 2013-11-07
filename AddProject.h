//---------------------------------------------------------------------------

#ifndef AddProjectH
#define AddProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TAddProjectForm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TEdit *ExecName;
    TGroupBox *GroupBox3;
    TEdit *ExamName;
    TGroupBox *GroupBox4;
    TEdit *RoadName;
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox5;
    TEdit *ProjName;
    TDBLookupComboBox *OrgName;
    TDataSource *DataSource1;
    TADODataSet *ADODataSet1;
    void __fastcall ProjNameChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAddProjectForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddProjectForm *AddProjectForm;
//---------------------------------------------------------------------------
#endif
