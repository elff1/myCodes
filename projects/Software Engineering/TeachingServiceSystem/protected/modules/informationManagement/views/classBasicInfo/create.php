<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('classBasicInfo','Class Basic Infos')=>array('index'),
	InformationManagementModule::t('classBasicInfo','Create ClassBasicInfo'),
);
//右侧菜单栏
$this->menu=array(
	//array('label'=>Yii::t('classBasicInfo','Create ClassBasicInfo'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('classBasicInfo','List ClassBasicInfo'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('classBasicInfo','Manage ClassBasicInfo'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('classBasicInfo','Batch Create Class'), 'url'=>array('batchCreate')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('classBasicInfo','Create ClassBasicInfo') . "</h1>"; ?>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>