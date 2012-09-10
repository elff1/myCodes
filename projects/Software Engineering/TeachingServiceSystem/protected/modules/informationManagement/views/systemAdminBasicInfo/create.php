<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('systemAdminBasicInfo','System Admin Basic Info')=>array('index'),
	InformationManagementModule::t('systemAdminBasicInfo','Create Basic Info'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('systemAdminBasicInfo','List Basic Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('systemAdminBasicInfo','Manage Basic Info'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('systemAdminBasicInfo', 'Create Basic Info')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model, 'personalInfoModel'=>$personalInfoModel)); ?>