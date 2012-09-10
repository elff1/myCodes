<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('program','Program')=>array('index'),
	InformationManagementModule::t('program','Create Program'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('program','List Program'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('program','Manage Program'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('program','Create Program')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>