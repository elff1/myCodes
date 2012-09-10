<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Teacher Basic Infos'=>array('index'),
	$model->title=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List TeacherBasicInfo', 'url'=>array('index')),
	array('label'=>'Create TeacherBasicInfo', 'url'=>array('create')),
	array('label'=>'View TeacherBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage TeacherBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Update TeacherBasicInfo <?php echo $model->id; ?></h1>
<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model,'personalInfoModel'=>$personalInfoModel)); ?>