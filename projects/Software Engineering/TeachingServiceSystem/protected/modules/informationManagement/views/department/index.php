<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('department','Departments'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('department','Create Department'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('department','Manage Department'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('department','Batch Create Department'), 'url'=>array('batchCreate')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('department','Departments') . "</h1>"; ?>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
