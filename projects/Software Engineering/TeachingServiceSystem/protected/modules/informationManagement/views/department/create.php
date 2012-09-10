<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('department','Departments')=>array('index'),
	InformationManagementModule::t('department','Create Department'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('department','List Department'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('department','Manage Department'), 'url'=>array('admin')),
);
?>

<?php echo "<h1>" . InformationManagementModule::t('department','Create Department') . "</h1>"; ?>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>