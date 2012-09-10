<?php
//顶部导航栏
$this->breadcrumbs=array(
	//'Personal Infos',
	InformationManagementModule::t('personalInfo','Personal Infos')
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('personalInfo','Create Personal Info'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('personalInfo','Manage Personal Info'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('personalInfo','Batch Create Personal Info'), 'url'=>array('batchCreate')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('personalInfo','Personal Infos') . "</h1>"; ?>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
