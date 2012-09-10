<?php
$this->breadcrumbs=array(
	InformationManagementModule::t('program','Program'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('program','Create Program'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('program','Manage Program'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('program','Batch Create Program'), 'url'=>array('batchCreate')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('program', 'Program')); ?></h1>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
