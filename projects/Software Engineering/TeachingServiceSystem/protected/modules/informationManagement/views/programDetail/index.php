<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('programDetail','Program Details'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('programDetail','Create ProgramDetail'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('programDetail','Manage ProgramDetail'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('programDetail', 'Program Details')); ?></h1>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
