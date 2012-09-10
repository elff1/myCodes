<div class="form">

<!-- the data input form -->
<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'paper-bank-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<!-- the teacher_id input row -->
	<div class="row">
		<?php echo $form->hiddenField($model,'teacher_id'); ?>
	</div>

	<!-- the course_id input row -->
	<div class="row">
		<?php echo $form->hiddenField($model,'course_id'); ?>
	</div>

	<!-- the is_publish input row -->
	<div class="row">
		<?php echo $form->hiddenField($model, 'is_publish'); ?>
	</div>

	<!-- the timelimit input row -->
	<div class="row">
		<?php echo $form->labelEx($model,'timelimit'); ?>
		<?php 
			$this->widget('ext.timepicker.EJuiDateTimePicker',array(
			    'model'=>$model,
			    'attribute'=>'timelimit',
			    'options'=>array(
			        'hourGrid' => 1,
			    	'minGrid'=>10,
			        'hourMin' => 0,
			        'hourMax' => 2,
			        'timeFormat' => 'h:m:s',
			        ),
			    ));  
		?>
		<?php echo $form->error($model,'timelimit'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->