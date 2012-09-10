<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('personalInfo','Personal Infos')=>array('index'),
	InformationManagementModule::t('personalInfo','Create Personal Info'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('personalInfo','List Personal Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('personalInfo','Manage Personal Info'), 'url'=>array('admin')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('personalInfo','Create Personal Info') . "</h1>"; ?>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>