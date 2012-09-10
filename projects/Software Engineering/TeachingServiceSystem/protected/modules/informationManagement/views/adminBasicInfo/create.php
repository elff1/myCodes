<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('adminBasicInfo','Admin Basic Info')=>array('index'),
	InformationManagementModule::t('adminBasicInfo','Create Basic Info'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('adminBasicInfo','List Basic Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('adminBasicInfo','Manage Basic Info'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('adminBasicInfo', 'Create Basic Info')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model, 'personalInfoModel'=>$personalInfoModel)); ?>