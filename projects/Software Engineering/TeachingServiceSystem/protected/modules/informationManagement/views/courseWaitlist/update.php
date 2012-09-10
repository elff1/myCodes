<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Course Waitlists'=>array('index'),
	$model->name=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List CourseWaitlist', 'url'=>array('index')),
	array('label'=>'Create CourseWaitlist', 'url'=>array('create')),
	array('label'=>'View CourseWaitlist', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage CourseWaitlist', 'url'=>array('admin')),
);
?>

<h1>Update CourseWaitlist <?php echo $model->id; ?></h1>

<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>