�
 TOPENROADDIALOG 0}  TPF0TOpenRoadDialogOpenRoadDialogLeft� Top� Width�HeightCaption   Справочник дорогColor	clBtnFaceFont.CharsetDEFAULT_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style 
KeyPreview	OldCreateOrder	PositionpoScreenCenter	OnKeyDownFormKeyDownOnShowFormShowPixelsPerInchx
TextHeight TDBGridDBGrid1Left Top)Width�Height~AlignalClient
DataSourceListRoads_DataSourceReadOnly	TabOrderTitleFont.CharsetDEFAULT_CHARSETTitleFont.ColorclWindowTextTitleFont.Height�TitleFont.NameMS Sans SerifTitleFont.Style 
OnDblClickDBGrid1DblClickColumnsExpanded	FieldNameid_Title.CaptionIDVisible	 Expanded	FieldName	FullTitleTitle.Caption   "8BC;Width� Visible	 Expanded	FieldNameStartPosTitle.Caption   0G0;>Width2Visible	 Expanded	FieldNameEndPosTitle.Caption   >=5FWidth2Visible	 Expanded	FieldNameDistTitle.Caption    09>=WidthdVisible	 Expanded	FieldNameOrgTitle.Caption!   Орг.провод.инвент.WidthdVisible	 Expanded	FieldNameLastInventYearTitle.Caption   Год инвент.Visible	 Expanded	FieldNameGrpTitle.Caption   "8BC;Width`Visible	    TPanelPanel1Left Top Width�Height)AlignalTop
BevelOuterbvNoneTabOrder  TPanelPanel3Left Top Width�Height)AlignalTopTabOrder  TPanelPanel4LeftTopWidth_Height'AlignalLeftAutoSize	
BevelOuterbvNoneBorderWidthTabOrder  TEdittxtIDFilterLeftTop	WidthLHeightTabOrder OnChange	SetFilter  TEdit	txtFilterLeft\Top	Width� HeightTabOrderOnChange	SetFilter   TPanelPanel5LeftTopWidth�Height'AlignalRightAutoSize	
BevelOuterbvNoneBorderWidthTabOrder
DesignSize�'  TButtonButton3LeftSTopWidth]HeightCaption	   >4B8BC;KTabOrder OnClickButton3Click  	TComboBoxcbGroupLeft� TopWidth� HeightStylecsDropDownListAnchorsakTopakRight DropDownCount
ItemHeightTabOrderOnChangecbGroupChangeItems.Strings    	TComboBoxcbDistLeftTopWidth� HeightStylecsDropDownListAnchorsakTopakRight DropDownCount
ItemHeightTabOrderOnChange	SetFilter     TPanelPanel2Left Top�Width�Height2AlignalBottom
BevelOuterbvNoneTabOrder TDBTextDBText1Left� TopWidthPHeight	DataFieldDist
DataSourceListRoads_DataSource  TButtonButton1LeftTop
Width\HeightCaptionOkModalResultTabOrder TabStopOnClickButton1Click  TButtonButton2LeftqTop
Width]HeightCaption   B<5=0ModalResultTabOrderTabStopOnClickButton1Click   TADODataSetListRoads_DataSet
ConnectionMainForm.Connection
CursorTypectStaticFiltered	AfterScrollListRoads_DataSetAfterScrollCommandText!  select R.id_,R.FullTitle,D.FullTitle as Dist, D.id_ as did,R.StartPos,R.EndPos,R.LastInventYear,
O.FullTitle as Org, R.Comments, G.FullTitle as Grp, T.NumGroup,
R.ParentRoad as pid 
from ListRoads R 
LEFT JOIN ListDistricts D ON R.NumDistrict=D.id_
LEFT JOIN ListOrganizations O ON R.InventOrg_id=O.id_
LEFT JOIN ((select NumRoad,NumGroup from ConnectRoadGroupTitle_M ) union
(select NumRoad,NumGroup from ConnectRoadGroupTitle) ) T on R.id_=T.NumRoad
LEFT JOIN ListTitleGroups G on T.NumGroup=G.id_
where R.id_<>0
order by R.FullTitle
Parameters Left Toph  TDataSourceListRoads_DataSourceDataSetListRoads_DataSetLeftPToph  TADODataSetSubTitul_DataSet
ConnectionMainForm.Connection
CursorTypectStaticFiltered	CommandText)  select R.id_ as rid ,R.FullTitle,D.FullTitle as Dist, D.id_ as did,R.StartPos,R.EndPos,R.LastInventYear,
O.FullTitle as Org, R.Comments, G.FullTitle as Grp, T.NumGroup,
R.ParentRoad as pid 
from ListRoads R 
LEFT JOIN ListDistricts D ON R.NumDistrict=D.id_
LEFT JOIN ListOrganizations O ON R.InventOrg_id=O.id_
LEFT JOIN ((select NumRoad,NumGroup from ConnectRoadGroupTitle_M ) union
(select NumRoad,NumGroup from ConnectRoadGroupTitle) ) T on R.id_=T.NumRoad
LEFT JOIN ListTitleGroups G on T.NumGroup=G.id_
where R.id_<>0
order by R.FullTitle
Parameters Left Top@   