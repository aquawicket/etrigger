//// SampleDialog.cpp //////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "SampleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////////////////////////////
BEGIN_EVENT_TABLE(SampleDialog, wxDialog) 
	EVT_LISTBOX(101, SampleDialog::OnSampleSelection)
	EVT_BUTTON(102, SampleDialog::OnImport)
END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////////////////////////////
SampleDialog::SampleDialog(TriggerDialog* parent) 
	     :wxDialog(parent, -1, wxT("Samples"), wxDefaultPosition, wxSize(520, 510), wxDEFAULT_DIALOG_STYLE)
{
	triggerDialog = parent;
	mainPanel = triggerDialog->trigger->trackProc->trackPanel->mainPanel;

	samples = new wxListBox(this, 101, wxPoint(10,40), wxSize(200,300), NULL, NULL,wxLB_SINGLE, wxDefaultValidator);
	sampleFolder = new wxStaticText(this, -1, wxT(""), wxPoint(240, 40), wxDefaultSize, 0, wxT("")); 
	image = new GImage(this, -1, wxPoint(240, 70));

	import = new wxButton(this, 102, wxT("Import"), wxPoint(10, 400), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	
	UpdateDialog();
}

///////////////////////
SampleDialog::~SampleDialog()
{
	delete image;
}

//////////////////////////////
void SampleDialog::UpdateDialog()
{
	PopulateSamples();	
}

////////////////////////////////////////////////
void SampleDialog::SetActiveSample(wxString folder)
{
	if(folder != wxT("")){
		for(unsigned int i=0; i<samples->GetCount(); ++i){
			if(mainPanel->samples->GetNameFromFolder(folder) == samples->GetString(i)){
				samples->SetSelection(i);
				sampleFolder->SetLabel(folder);
				image->SetImage(folder += wxT("\\Sample.bmp"));
				return;
			}
		}
	}
}

/////////////////////////////////
void SampleDialog::PopulateSamples()
{
	samples->Clear();

	//here we need a list of samples in the sample folder
	mainPanel->samples->GetSampleFolders();
	wxArrayString names = mainPanel->samples->GetSampleNames();
	for(unsigned int i=0; i< names.Count(); ++i){
		samples->Insert(names.Item(i), 0);
	}
}

////////////////////////////////////////////////////////
void SampleDialog::OnSampleSelection(wxCommandEvent &event)
{
	wxString folder = mainPanel->samples->GetFolderFromName(samples->GetString(samples->GetSelection()));
	sampleFolder->SetLabel(folder);
	triggerDialog->SetSampleFolder(folder);
	image->SetImage(folder += wxT("\\Sample.bmp"));
}

///////////////////////////////////////////////
void SampleDialog::OnImport(wxCommandEvent &event)
{

}