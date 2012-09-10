<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('programDetail','Program Details')=>array('index'),
	InformationManagementModule::t('programDetail','Create'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('programDetail','List ProgramDetail'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('programDetail','Manage ProgramDetail'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('programDetail', 'Create ProgramDetail')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>