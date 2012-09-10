<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('personalInfo','Personal Infos')=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	InformationManagementModule::t('personalInfo','Update Personal Info'),
);

//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('personalInfo','List Personal Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('personalInfo','Create Personal Info'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('personalInfo','View Personal Info'), 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>InformationManagementModule::t('personalInfo','Manage Personal Info'), 'url'=>array('admin')),
);
?>

<h1>Update PersonalInfo <?php echo $model->id; ?></h1>

<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>