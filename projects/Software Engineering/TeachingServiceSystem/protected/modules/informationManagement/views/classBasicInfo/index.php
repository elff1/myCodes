<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('classBasicInfo','Class Basic Infos'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('classBasicInfo','Create ClassBasicInfo'), 'url'=>array('create')),
	//array('label'=>InformationManagementModule::t('classBasicInfo','List ClassBasicInfo'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('classBasicInfo','Manage ClassBasicInfo'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('classBasicInfo','Batch Create Class'), 'url'=>array('batchCreate')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('classBasicInfo','Class Basic Infos') . "</h1>"; ?>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
