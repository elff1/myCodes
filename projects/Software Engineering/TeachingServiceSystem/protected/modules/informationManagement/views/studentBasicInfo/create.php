<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('studentBasicInfo','Student Basic Info')=>array('index'),
	InformationManagementModule::t('studentBasicInfo','Create Basic Info'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('studentBasicInfo','List Basic Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('studentBasicInfo','Manage Basic Info'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('studentBasicInfo', 'Create Basic Info')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model, 'personalInfoModel'=>$personalInfoModel)); ?>